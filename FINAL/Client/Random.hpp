#ifndef CLIENT_RANDOM_HPP
#define CLIENT_RANDOM_HPP

#include <random>
#include <utility>
#include <algorithm>
#include <iostream>

extern std::mt19937 rng;

template<typename Range, typename Predicate>
auto findBest(const Range& range, const Predicate& predicate) {
    using Element = typename Range::value_type;
    using Value = decltype(predicate(std::declval<Element>()));
    using Iterator = typename Range::const_iterator;
    std::vector<std::pair<Value, Iterator>> elements;
    for (auto it = range.begin(); it != range.end(); ++it) {
        elements.emplace_back(predicate(*it), it);
        //std::cerr << elements.back().first << " " <<
                //elements.back().second << "\n";
    }
    std::sort(elements.begin(), elements.end(),
            [](const auto& lhs, const auto& rhs) {
                return lhs.first < rhs.first;
            });
    std::size_t i = 0;
    for (i = 0; i < elements.size(); ++i) {
        //std::cerr << "--> " << elements[i].first << " " <<
                //elements[i].second << "\n";
        if (elements[i].first != elements[0].first) {
            break;
        }
    }
    std::uniform_int_distribution<std::size_t> dist{0, i - 1};
    std::size_t num = dist(rng);
    //std::cerr << "++>" << num << ": " << elements[num].first << " " <<
            //elements[num].second << "\n";
    return elements[num].second;
}

template<typename Range>
auto randomizedRange(const Range& range) {
    std::vector<typename Range::value_type> result;
    std::copy(range.begin(), range.end(), std::back_inserter(result));
    std::shuffle(result.begin(), result.end(), rng);
    return result;
}

#endif // CLIENT_RANDOM_HPP
