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

using Strings = std::vector<const char*>;

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
int charAt(const char* s, int d) {
    const int len = strlen(s);
    assert(d >= 0 && d <= len);
    if (d == len) return -1;
    return alphaToIndex(s[d]);
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

bool less(const char* v, const char* w, int d);

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
bool less(const char* v, const char* w, int d) {
    // assert v.substring(0, d).equals(w.substring(0, d));
    const int v_len = strlen(v);
    const int w_len = strlen(w);
    for (int i = d; i < std::min(v_len, w_len); i++) {
        if (v[i] < w[i]) return true;
        if (v[i] > w[i]) return false;
    }
    return v_len < w_len;
}

std::ostream& operator<<(std::ostream& os, const Strings& ss) {
    for (const auto& s: ss) {
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
    sort(s2);
    std::cout << s;
    std::cout << "----\n";
    std::cout << s2;
    ASSERT(s == s2);
}

void test2() {
    Strings s{
       "gzhwclin",
       "glerwlm",
       "jiwhnswg",
       "lwwrfs",
       "lcmgfdc",
       "srxrch",
       "auxlmc",
       "jqqw",
       "ogrm",
       "otqsv",
       "froidbtcj",
       "vnip",
       "ecmxtxawrv",
       "eqvkbyyhas",
       "ijfdgemu",
       "autmofg",
       "hkvuiieku",
       "enhhdxu",
       "lojd",
       "gbhsnqpz"};
    Strings s2(s);
    std::sort(s.begin(), s.end(), [](const char* lhs, const char* rhs) {
                return strcmp(lhs, rhs) < 0;
            });
    std::cout << s;
    sort(s2);
    std::cout << s2;
    ASSERT(s == s2);
}

int test() {
    test1();
    test2();
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
    //std::cin.rdbuf()->pubsetbuf(Buffer, BufSize);
    array.resize(num * 65);
    std::vector<const char*> vector;
    vector.resize(num);
    std::size_t i = 0;
    std::size_t index = 0;
    vector[0] = &array[0];

    const int BufSize = 4*1024*1024;
    std::vector<char> rBuffer(BufSize);
    int bytesInBuffer = std::fread(&rBuffer[0], sizeof rBuffer[0],
            rBuffer.size(), stdin);
    while(bytesInBuffer != 0) {
        int readFromBuffer = 0;
        while (readFromBuffer < bytesInBuffer) {
            array[index] = rBuffer[readFromBuffer];
            if (array[index] == '\n') {
                ++i;
                array[index] = '\0';
                // TODO cache locality
                index = i * 65;
                vector[i] = &array[index];
            } else {
                ++index;
            }
            ++readFromBuffer;
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

    std::copy(vector.begin(), vector.end(),
            std::ostream_iterator<const char*>(std::cout, "\n"));
    auto write_end = Clock::now().time_since_epoch().count();
    //std::cout << vector;
    std::cerr << "Write took: " << (write_end - sort_end) / double(Den) * Num << std::endl;
    return 0;
}
