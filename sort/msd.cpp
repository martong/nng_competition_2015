#include <string>
#include <vector>
#include <cassert>
#include <iostream>
#include <array>
#include <algorithm>

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

using Strings = std::vector<std::string>;

void sort(Strings& a, int lo, int hi, int d, Strings& aux);

/**
 * Rearranges the array of extended ASCII strings in ascending order.
 *
 * @param a the array to be sorted
 */
void sort(Strings& a) {
    int N = a.size();
    Strings aux(N);
    sort(a, 0, N-1, 0, aux);
}

int alphaToIndex(char c) {
    return c - 'a';
}

// return dth character of s, -1 if d = length of string
int charAt(const std::string& s, int d) {
    assert(d >= 0 && d <= (int)s.length());
    if (d == (int)s.length()) return -1;
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
        aux[count[c+1]++] = a[i];
    }

    // copy back
    for (int i = lo; i <= hi; i++)
        a[i] = aux[i - lo];


    // recursively sort for each character (excludes sentinel -1)
    for (int r = 0; r < R; r++)
        sort(a, lo + count[r], lo + count[r+1] - 1, d+1, aux);
}

void exch(Strings& a, int i, int j);

bool less(const std::string& v, const std::string& w, int d);

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
bool less(const std::string& v, const std::string& w, int d) {
    // assert v.substring(0, d).equals(w.substring(0, d));
    for (int i = d; i < (int)std::min(v.length(), w.length()); i++) {
        if (v[i] < w[i]) return true;
        if (v[i] > w[i]) return false;
    }
    return v.length() < w.length();
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
    std::sort(s.begin(), s.end());
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
    std::sort(s.begin(), s.end());
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
    std::size_t num;
    std::cin >> num;
    Strings strings;
    strings.reserve(num);
    while (std::cin.good()) {
        std::string s;
        std::getline(std::cin, s, '\n');
        if (!s.empty()) {
            strings.push_back(std::move(s));
        }
    }
    std::cerr << strings.size() << '\n';
    assert(strings.size() == num);
    sort(strings);
    std::cout << strings;
    return 0;
}
