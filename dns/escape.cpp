#include <iostream>
#include <iomanip>

int main() {
    std::cout << R"(#include <iostream>
int main() {
    std::cout << ")";
    unsigned char c;
    bool wasNull = false;
    while (std::cin.get(reinterpret_cast<char&>(c)).good()) {
        switch (c) {
        case '\0':
            std::cout << "\\0";
            break;
        case '\a':
            std::cout << "\\a";
            break;
        case '\b':
            std::cout << "\\b";
            break;
        case '\f':
            std::cout << "\\f";
            break;
        case '\n':
            std::cout << "\\n";
            break;
        case '\r':
            std::cout << "\\r";
            break;
        case '\t':
            std::cout << "\\t";
            break;
        case '\v':
            std::cout << "\\v";
            break;
        case '\\':
            std::cout << "\\\\";
            break;
        case '"':
            std::cout << "\\\"";
            break;
        default:
            if (c < 0x20 || (c >= 0x7f && c < 0xa0)) {
                std::cout << "\\" << std::oct << std::setw(3) <<
                        std::setfill('0') << (int)c;
            } else if (wasNull && c >= '0' && c <= '9') {
                std::cout << "00" << c;
            } else {
                std::cout << c;
            }
        }
        wasNull = c == '\0';
    }
    std::cout << "\";\n}\n";
    return 0;
}
