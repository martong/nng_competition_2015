#ifndef DNS_HUFFMAN_HPP
#define DNS_HUFFMAN_HPP

#include <iostream>
#include <iomanip>

#include <algorithm>
#include <bitset>
#include <cassert>
#include <cstdint>
#include <map>
#include <queue>
#include <fstream>

struct Node {
    Node(char symbol, unsigned probability)
            : symbol(symbol),
              probability(probability),
              left(nullptr),
              right(nullptr) {
    }

    char symbol;
    unsigned probability;
    Node* left;
    Node* right;
};

Node* createTree(std::map<char, unsigned> probabilities) {
    std::vector<std::pair<std::uint16_t, Node*>> nodes;
    for (const auto& pair : probabilities) {
        assert(pair.first != 'n');
        assert(pair.first != 'e');
        nodes.push_back({pair.second, new Node{pair.first, pair.second}});
    }

    while (nodes.size() > 1) {
        auto it = std::min_element(nodes.begin(), nodes.end());
        Node* firstLowest = it->second;
        nodes.erase(it);
        it = std::min_element(nodes.begin(), nodes.end());
        Node* secondLowest = it->second;
        nodes.erase(it);
        auto n = new Node('n', firstLowest->probability +
                secondLowest->probability);
        n->left = firstLowest;
        n->right = secondLowest;
        nodes.push_back({n->probability, n});
    }
    return nodes.begin()->second;
}

int getTreeHeight(Node* root) {
    if (!root) {
        return -1;
    }
    int left = getTreeHeight(root->left);
    int right = getTreeHeight(root->right);
    return 1 + std::max(left, right);
}

bool isLeaf(Node* root) {
    return !root->left && !root->right;
}

std::string toString(Node* root) {
    // Basically this is a preorder BFS.
    // The tree is not balanced, therefore first we need to create a
    // string  that holds empt elements and that is proportional to the height
    // of the tree.
    std::string output(1 << (getTreeHeight(root)+1), 'e');
    std::queue<std::pair<Node*, int>> q;
    q.push({root, 1});
    while (!q.empty()) {
        auto p = q.front();
        q.pop();
        Node* n = p.first;
        int index = p.second;
        output[index] = n->symbol;
        if (n->left) {
            q.push({n->left, 2 * index});
        }
        if (n->right) {
            q.push({n->right, 2 * index + 1});
        }

    }
    return output;
}

void printTree(Node* root, int indent = 0) {
    if (root) {
        if (indent > 0) {
            for (int i = 4; i < indent; ++i) {
                std::cout << ' ';
            }
            std::cout << "----";
        }
        std::cout << root->symbol << std::endl;
        if (root->left) {
            printTree(root->left, indent+4);
        }
        if (root->right) {
            printTree(root->right, indent+4);
        }
    }
}

void generateCodes(Node* root,
        std::map<char, std::pair<char, std::uint16_t>>& codes,
        char size = 0, std::uint16_t value = 0) {
    if (!root->left && !root->right) { // it is a leaf
        assert(root->symbol != 'n');
        assert(root->symbol != 'e');
        codes[root->symbol] = {size, value};
    } else {
        value <<= 1;
        ++size;
        if (root->left) {
            generateCodes(root->left, codes, size, value);
        }
        if (root->right) {
            generateCodes(root->right, codes, size, value + 1);
        }
    }
}

std::pair<unsigned, std::string> encodeString(std::map<char, std::pair<char,
        std::uint16_t>> codes, std::string input) {
    std::string output;
    unsigned char encoded = 0;
    char bits = 8;
    unsigned numberOfBits = 0;
    for (char c : input) {
        const auto& code = codes[c];
        // std::cout << "code: {" << (int)code.first << ',' << code.second << '}'
        //           << " bits: " << (int)bits << " numberOfBits: "
        //           << numberOfBits << std::endl;
        assert(bits >= 0 && bits <= 8);
        assert(numberOfBits >= (8*output.size()) && (numberOfBits) <= (8*output.size()+8));
        if (bits == 0) {
            output.append(1, encoded);
            // std::cout << "appending char " << (int)encoded << " numberOfBits: "
            //           << numberOfBits << " characters: " << output.size()
            //           << std::endl;
            encoded = 0;
            bits = 8;
        }
        numberOfBits += code.first;
        if (code.first <= bits) {
            encoded <<= code.first;
            encoded += code.second;
            bits -= code.first;
        } else {
            char remainingBits = code.first - bits;
            assert(remainingBits < 15);
            encoded <<= bits;
            encoded += (code.second >> remainingBits);
            output.append(1, encoded);
            // std::cout << "appending char " << (int)encoded << " size so far: "
            //           << numberOfBits << " character: " << output.size()
            //           << std::endl;
            if (remainingBits >= 8) {
                encoded = 0;
                encoded += ((code.second >> (remainingBits - 8)) & 255);
                output.append(1, encoded);
                // std::cout << "appending char " << (int)encoded << " size so far: "
                //           << numberOfBits << ' ' << output.size() << std::endl;
                bits = 16 - remainingBits;
                remainingBits -= 8;
            }
            encoded = 0;
            encoded += (code.second & (255 >> (8 - remainingBits)));
            bits = 8 - remainingBits;
        }
    }
    if (bits != 8) {
        encoded <<= bits;
        output.append(1, encoded);
    }
    return  {numberOfBits, output};
}

std::string decodeString(std::map<std::pair<char, std::uint16_t>, char> codes,
        unsigned numberOfBits, std::string input) {
    std::string output;
    auto it = input.begin();
    std::bitset<8> bitset = *it++;
    char bit = 7;
    char size = 0;
    std::uint16_t n = 0;
    while (numberOfBits > 0) {
        ++size;
        n <<= 1;
        n += bitset.test(bit--);
        // std::cout << "searching for: {"
        //           << (int)size << ", " << n << "} bitset: " << bitset
        //           << " bit: " << (int)bit << " size: " << (int)size
        //           << " numberOfBits: " << numberOfBits
        //           << " output: " << output.size() << std::endl;
        if (codes.count({size, n}) > 0) {
            // std::cout << "Found a character: " << (int)codes[{size, n}]
            //           << " size: " << (int)size << " bit: " << (int)bit
            //           << " n: " << (int)n << std::endl;
            output.append(1, codes[{size, n}]);
            size = 0;
            n = 0;
        }
        --numberOfBits;
        if (bit == -1 && numberOfBits > 0) {
            bit = 7;
            assert(it != input.end());
            bitset = *it++;
        }
        //std::cout << "numberOfBits: " << numberOfBits << std::endl;
    }
    return output;
}

std::string mapToString(std::map<char, std::pair<char, std::uint16_t>> map) {
    std::string result;
    for (const auto& element : map) {
        result += {element.first, element.second.first,
                static_cast<char>(element.second.second & 0xff),
                static_cast<char>(element.second.second >> 8),
        };
    }
    return result;
}

std::map<std::pair<char, std::uint16_t>, char> stringToMap(std::string data) {
    std::map<std::pair<char, std::uint16_t>, char> result;
    assert(data.size() % 4 == 0);
    for (std::size_t i = 0; i < data.size(); i += 4) {
        result.insert({{data[i+1], (uint8_t)data[i+2] + (data[i+3] << 8)}, data[i]});
    }
    return result;
}

std::string decodeString(std::string codeTree, unsigned numberOfBits,
        std::string input) {
    std::string output;
    auto it = input.begin();
    std::bitset<8> bitset = *it++;
    char bit = 7;
    int index = 1;
    // char size = 0;
    // std::uint16_t n = 0;
    while (numberOfBits > 0) {
        while (codeTree[index] == 'n') {
            assert(codeTree[index] != 'e');
            --numberOfBits;
            if (bitset[bit--]) { // right branch
                index = index * 2 + 1;
            } else { // left branch
                index = index * 2;
            }
            if (bit == -1 && numberOfBits > 0) {
                bit = 7;
                assert(it != input.end());
                bitset = *it++;
            }
        }
        output.append(1, codeTree[index]);
        index = 1;
    }
    return output;
}

#endif // DNS_HUFFMAN_HPP
