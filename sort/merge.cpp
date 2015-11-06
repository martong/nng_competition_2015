/**
 * This is an MSD sort algorithm, sourced from Sedgewick's original
 * MSD implementation for Java.
 * See http://algs4.cs.princeton.edu/51radix/MSD.java.html
 **/

#include <string>
#include <vector>
#include <cassert>
#include <iostream>
#include <array>
#include <algorithm>
#include <thread>
#include <future>
#include <chrono>
#include <iterator>
#include <cstring>
#include <string.h>

#define ASSERT(CONDITION)                                                      \
    do                                                                         \
        if (!(CONDITION)) {                                                    \
            printf("Assertion failure %s:%d ASSERT(%s)\n", __FILE__, __LINE__, \
                   #CONDITION);                                                \
            abort();                                                           \
        }                                                                      \
    while (0)

using Strings = std::vector<const char*>;

void sort(Strings& a, std::size_t lo, std::size_t hi) {
    if (lo >= a.size() - 1) return;
    if (hi > a.size()) hi = a.size();
    std::sort(
        a.begin() + lo, a.begin() + hi,
        [](const char* lhs, const char* rhs) { return strcmp(lhs, rhs) < 0; });
}

void merge(Strings& a, Strings& aux, int lo, int mid, int hi) {
    // precondition: a[lo .. mid] and a[mid+1 .. hi] are sorted subarrays
    // assert isSorted(a, lo, mid);
    // assert isSorted(a, mid+1, hi);
    // std::cout << lo << " " << mid << " " << hi << std::endl;
    // return;

    assert(lo <= a.size() - 1);
    assert(hi <= a.size() - 1);

    // copy to aux[]
    for (int k = lo; k <= hi; k++) {
        aux[k] = a[k];
    }

    // merge back to a[]
    int i = lo, j = mid + 1;
    for (int k = lo; k <= hi; k++) {
        if (i > mid)
            a[k] = aux[j++];
        else if (j > hi)
            a[k] = aux[i++];
        // else if (less(aux[j], aux[i])) a[k] = aux[j++];
        else if (strcmp(aux[j], aux[i]) < 0)
            a[k] = aux[j++];
        else
            a[k] = aux[i++];
    }

    // postcondition: a[lo .. hi] is sorted
    // assert isSorted(a, lo, hi);
}

using Future = std::future<void>;
using Futures = std::vector<Future>;
using Bounds = std::vector<std::tuple<int, int>>;

void mergeR(Strings& a, Strings& aux, const Bounds& bounds) {
    std::vector<std::tuple<int, int>> bounds2;
    if (bounds.size() <= 1) {
        return;
    }
    Futures futures;
    for (int i = 0; i < bounds.size(); i += 2) {
        auto lo = std::get<0>(bounds.at(i));
        auto mid = std::get<0>(bounds.at(i + 1));
        auto hi = std::get<1>(bounds.at(i + 1));
        Future f = std::async(std::launch::async, [&a, &aux, mid, lo, hi]() {
            merge(a, aux, lo, mid - 1, hi - 1);
        });
        bounds2.push_back({lo, hi});
        futures.push_back(std::move(f));
    }
    for (auto& f : futures) {
        f.get();
    }
    mergeR(a, aux, bounds2);
}

void sort(Strings& a) {
    const int N = 16;
    assert(N < a.size());
    const double M = a.size() / double(N);
    Bounds bounds;
    Futures futures;
    for (double i = 0.0; i < a.size(); i += M) {
        bounds.push_back({i, i + M});
        // std::cout << i << " " << i + M << std::endl;
        Future f =
            std::async(std::launch::async, [&a, i, M]() { sort(a, i, i + M); });
        futures.push_back(std::move(f));
    }
    for (auto& f : futures) {
        f.get();
    }
    Strings aux(a.size());
    mergeR(a, aux, bounds);
}

// void sort(Strings& a) {
// std::sort(a.begin(), a.end(),
//[](const char* lhs, const char* rhs) {
// return strcmp(lhs, rhs) < 0;
//});
//}

std::ostream& operator<<(std::ostream& os, const Strings& ss) {
    for (const auto& s : ss) {
        os << s << "\n";
    }
    return os;
}

void test1() {
    Strings s{"zzz", "fee", "eee", "ee", "aaaa"};
    Strings s2(s);
    std::sort(s.begin(), s.end(), [](const char* lhs, const char* rhs) {
        return strcmp(lhs, rhs) < 0;
    });
    std::cout << s;
    std::cout << "----\n";
    sort(s2);
    std::cout << s2;
    ASSERT(s == s2);
}

void test2() {
    Strings s{"gzhwclin",  "glerwlm",   "jiwhnswg",   "lwwrfs",     "lcmgfdc",
              "srxrch",    "auxlmc",    "jqqw",       "ogrm",       "otqsv",
              "froidbtcj", "vnip",      "ecmxtxawrv", "eqvkbyyhas", "ijfdgemu",
              "autmofg",   "hkvuiieku", "enhhdxu",    "lojd",       "gbhsnqpz"};
    Strings s2(s);
    std::sort(s.begin(), s.end(), [](const char* lhs, const char* rhs) {
        return strcmp(lhs, rhs) < 0;
    });
    std::cout << s;
    std::cout << "----\n";
    sort(s2);
    std::cout << s2;
    ASSERT(s == s2);
}

uint64_t modulo16(const char* s) { return 0xf & (uint64_t)s; }

void test3() {
    ASSERT(modulo16((const char*)1));
    ASSERT(!modulo16((const char*)16));
    ASSERT(!modulo16((const char*)0));
}

int test() {
    // test1();
    test2();
    test3();
    return 0;
}

int main() {

    using Clock = std::chrono::high_resolution_clock;
    constexpr auto Den = Clock::period::den;
    constexpr auto Num = Clock::period::num;

    auto start = Clock::now().time_since_epoch().count();

    std::size_t num;
    std::cin >> num;
    char ch = std::cin.get();
    static_cast<void>(ch);
    assert(ch == '\n');

    std::vector<char> array;
    // std::cin.rdbuf()->pubsetbuf(Buffer, BufSize);
    array.resize(num * 66);
    std::vector<const char*> vector;
    vector.resize(num);
    std::size_t string_index = 0; // indexes into vector, refs the nth string

    // array[0] contains the length of the 0th string
    std::size_t index = 0; // indexes into array
    while (modulo16(&array[index]) != 0) {
        ++index;
    }
    vector[0] = &array[0];

    const int BufSize = 4 * 1024 * 1024;
    std::vector<char> rBuffer(BufSize);
    int bytesInBuffer =
        std::fread(&rBuffer[0], sizeof rBuffer[0], rBuffer.size(), stdin);
    while (bytesInBuffer != 0) {
        int readFromBuffer = 0;
        while (readFromBuffer < bytesInBuffer) {
            array[index] = rBuffer[readFromBuffer];
            if (array[index] == '\n') {

                ++string_index;
                // We can use strlen, and check against 0 is faster than
                // check against '\n'
                array[index++] = '\0';
                while (modulo16(&array[index]) != 0) {
                    ++index;
                }
                if (string_index < num) {
                    vector[string_index] = &array[index];
                }
            } else {
                ++index;
            }
            ++readFromBuffer;
        }
        bytesInBuffer =
            std::fread(&rBuffer[0], sizeof rBuffer[0], rBuffer.size(), stdin);
    }

    std::cerr << "read done\n";

    auto read_end = Clock::now().time_since_epoch().count();
    std::cerr << "Read took: " << (read_end - start) / double(Den) * Num
              << std::endl;

    auto sort_start = Clock::now().time_since_epoch().count();
    sort(vector);
    auto sort_end = Clock::now().time_since_epoch().count();
    std::cerr << "Sort took: " << (sort_end - sort_start) / double(Den) * Num
              << std::endl;

    const int wBufSize = 4 * 1024 * 1024;
    std::vector<char> wBuffer(wBufSize);
    int wroteToBuffer = 0;
    for (const char* s : vector) {
        int i = 0;
        while (s[i] != '\0') wBuffer[wroteToBuffer++] = s[i++];
        wBuffer[wroteToBuffer++] = '\n';
        // TODO branch prediction hint (?)
        if (wBufSize - wroteToBuffer - 64 < 0) {
            std::fwrite(&wBuffer[0], sizeof wBuffer[0], wroteToBuffer, stdout);
            wroteToBuffer = 0;
        }
    }
    if (wBufSize - wroteToBuffer - 64 >= 0) {
        std::fwrite(&wBuffer[0], sizeof wBuffer[0], wroteToBuffer, stdout);
        wroteToBuffer = 0;
    }

    auto write_end = Clock::now().time_since_epoch().count();
    std::cerr << "Write took: " << (write_end - sort_end) / double(Den) * Num
              << std::endl;
    return 0;
}
