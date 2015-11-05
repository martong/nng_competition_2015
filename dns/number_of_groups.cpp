#include <iostream>
#include <fstream>

int main() {
    //std::string str = "AAACCTTGGGGTTCACCAAAC";
    //str = "baaaaaaaaaaaaaaaaaaaaaaaaaaaaa";

    std::ifstream t("dns_bwt_c4.txt");
    std::string str((std::istreambuf_iterator<char>(t)),
            std::istreambuf_iterator<char>());
    t.close();


    std::string::size_type found = 0, nextFound = 0;
    int groups = 1;
    while (found < str.size()) {
        nextFound = str.find_first_not_of(str[found], found);
        if (nextFound != std::string::npos) {
            ++groups;
        } else {
            nextFound = str.size();
        }
        found = nextFound;
    }
    std::cout << groups << std::endl;
}
