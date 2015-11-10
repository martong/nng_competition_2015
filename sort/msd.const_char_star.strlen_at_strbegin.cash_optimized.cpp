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
#include <cstdlib>
#include <string.h>

#define ASSERT(CONDITION)                                                      \
    do                                                                         \
        if (!(CONDITION)) {                                                    \
            printf("Assertion failure %s:%d ASSERT(%s)\n", __FILE__, __LINE__, \
                   #CONDITION);                                                \
            abort();                                                           \
        }                                                                      \
    while (0)

const int R             =  26;
const int CUTOFF        =  15;   // cutoff to insertion sort

struct String {
    int length;
    const char* data;
};

using Strings = std::vector<String>;

void sort(Strings& a, int lo, int hi, int d, Strings& aux);

void sort(Strings& a) {
    int N = a.size();
    Strings aux(N);
    sort(a, 0, N-1, 0, aux);
}

int alphaToIndex(char c) {
    return c - 'a';
}

// return dth character of s, -1 if d = length of string
int charAt(const String& s, int d) {
    //assert(d >= 0 && d <= len);
    if (d == s.length) return -1;
    return alphaToIndex(s.data[d]);
}

void insertion(Strings& a, int lo, int hi, int d);

// sort from a[lo] to a[hi], starting at the dth character
void sort(Strings& a, int lo, int hi, int d, Strings& aux) {

    // cutoff to insertion sort for small subarrays
    if (hi <= lo + CUTOFF) {
        insertion(a, lo, hi, d);
        return;
    }

    // compute frequency counts
    std::array<int, R + 2> count;
    count.fill(0);
    for (int i = lo; i <= hi; i++) {
        int c = charAt(a[i], d);
        count[c+2]++;
    }

    // transform counts to indicies
    for (int r = 0; r < R+1; r++)
        count[r+1] += count[r];

    // distribute
    for (int i = lo; i <= hi; i++) {
        int c = charAt(a[i], d);
        aux[count[c+1]++] = std::move(a[i]);
    }

    // copy back
    for (int i = lo; i <= hi; i++)
        a[i] = std::move(aux[i - lo]);


    if (d == 0) {
        using Future = std::future<void>;
        using Futures = std::vector<Future>;
        Futures futures;
        // recursively sort for each character (excludes sentinel -1)
        for (int r = 0; r < R; r++) {
            Strings new_aux(count[r+1] - count[r] + 1);
            Future f = std::async(std::launch::async, [&a, &count, lo, r, d, new_aux = std::move(new_aux)]() mutable {
                sort(a, lo + count[r], lo + count[r+1] - 1, d+1, new_aux);
            });
            futures.push_back(std::move(f));
        }
        for (auto& f : futures) {
            f.get();
        }
    }
    else {
        for (int r = 0; r < R; r++)
            sort(a, lo + count[r], lo + count[r+1] - 1, d+1, aux);
    }

}

void exch(Strings& a, int i, int j);

bool less(const String& v, const String& w, int d);

// insertion sort a[lo..hi], starting at dth character
void insertion(Strings& a, int lo, int hi, int d) {
    for (int i = lo; i <= hi; i++)
        for (int j = i; j > lo && less(a[j], a[j-1], d); j--)
            exch(a, j, j-1);
}

// exchange a[i] and a[j]
void exch(Strings& a, int i, int j) {
    std::swap(a[i], a[j]);
}

// is v less than w, starting at character d
bool less(const String& v, const String& w, int d) {
    // assert v.substring(0, d).equals(w.substring(0, d));
    for (int i = d; i < std::min(v.length, w.length); i++) {
        if (v.data[i] < w.data[i]) return true;
        if (v.data[i] > w.data[i]) return false;
    }
    return v.length < w.length;
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
    //std::cin.rdbuf()->pubsetbuf(Buffer, BufSize);
    array.resize(num * 65);
    Strings vector(num);
    std::size_t string_index = 0; // indexes into vector, refs the nth string

    // array[0] contains the length of the 0th string
    std::size_t index = 0; // indexes into array

    constexpr int BufSize = 256*1024;
    std::array<char, BufSize> rBuffer;
    int bytesInBuffer = std::fread(&rBuffer[0], sizeof rBuffer[0],
            rBuffer.size(), stdin);
    int remainingLength = 0;
    int currentStringBegin = 0;
    while(bytesInBuffer != 0) {
        int bufferIndex = 0;
        while (bufferIndex < bytesInBuffer) {
            int i = 0;
            while (rBuffer[bufferIndex + i] != '\n' && bufferIndex + i < bytesInBuffer - 1) ++i;
            std::memcpy(&array[index], &rBuffer[bufferIndex], i);
            bufferIndex += i;
            index += i;
            if (rBuffer[bufferIndex++] == '\n') {
                vector[string_index].length = i + remainingLength;
                vector[string_index++].data = &array[currentStringBegin];
                currentStringBegin = index;
                remainingLength = 0;
            } else {
                remainingLength = i;
            }
        }

        bytesInBuffer = std::fread(&rBuffer[0], sizeof rBuffer[0],
                rBuffer.size(), stdin);
    }

    std::cerr << "read done\n";

    auto read_end = Clock::now().time_since_epoch().count();
    std::cerr << "Read took: " << (read_end - start) / double(Den) * Num << std::endl;

    auto sort_start = Clock::now().time_since_epoch().count();
    sort(vector);
    auto sort_end = Clock::now().time_since_epoch().count();
    std::cerr << "Sort took: " << (sort_end - sort_start) / double(Den) * Num << std::endl;

    constexpr int wBufSize = 256*1024;
    std::array<char, wBufSize> wBuffer;
    int wroteToBuffer = 0;
    for (const String& s: vector) {
        std::memcpy(&wBuffer[wroteToBuffer], s.data, s.length);
        wroteToBuffer += s.length;
        wBuffer[wroteToBuffer++] = '\n';
        // TODO branch prediction hint (?)
        if (wBufSize - wroteToBuffer - 64 <= 0) {
            std::fwrite(&wBuffer[0], sizeof wBuffer[0], wroteToBuffer, stdout);
            wroteToBuffer = 0;
        }
    }
    if (wBufSize - wroteToBuffer - 64 >= 0) {
        std::fwrite(&wBuffer[0], sizeof wBuffer[0], wroteToBuffer, stdout);
        wroteToBuffer = 0;
    }

    auto write_end = Clock::now().time_since_epoch().count();
    std::cerr << "Write took: " << (write_end - sort_end) / double(Den) * Num << std::endl;
    return 0;
}
