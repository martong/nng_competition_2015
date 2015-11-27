#ifndef DUMPERFUNCTIONS_H_
#define DUMPERFUNCTIONS_H_

#include "Array.hpp"
#include <iostream>
#include <string>
#include <boost/format.hpp>
#include <boost/lexical_cast.hpp>

template<class T>
void dumpArray(std::ostream& file, const Array<T> table,
        const std::string& title = "", int indent = 0) {
    std::string indentString(indent, ' ');
    if (!title.empty()) {
        file << indentString << title << std::endl;
    }
    Array<std::string> txts(table.width(), table.height());
    size_t maxlen = 0;
    for (Point  p: arrayRange(table)) {
        txts[p] = boost::lexical_cast<std::string>(table[p]);
        maxlen = std::max(maxlen, txts[p].size());
    }
    // leave a space between characters
    ++maxlen;
    Point p;
    for (p.y = 0; p.y < static_cast<int>(table.height()); p.y++) {
        file << indentString;
        for (p.x = 0; p.x < static_cast<int>(table.width()); p.x++) {
            file.width(maxlen);
            file << txts[p];
        }
        file << std::endl;
    }
    file << std::endl;
}


#endif /* DUMPERFUNCTIONS_H_ */
