// cesun, 9/20/20 11:58 PM.

/*
 * Lex comparison.
 *
 * Derive the partial order of `T[]` when the partial order of `T` is defined;
 */

#include <string>

using std::string;

static int mag[128]; // map ascii to new letter ranking (leetcode 953)
// lex compare a <= b
bool le(const string &a, const string &b) {
    for (int i = 0; i < a.size(); ++i) {
        if (i < b.size()) {
            if (a[i] == b[i]) continue;
            return mag[a[i]] < mag[b[i]];
        }
        return false;
    }
    return true;
}

// lex compare a <= b; require < defined for T
template<typename T_it>
bool le(const T_it abegin, const T_it aend, const T_it bbegin, const T_it bend) {
    for (T_it it = abegin; it != aend; ++it) {
        if (it - abegin < bend - bbegin) {
            const T_it bit = bbegin + (it - abegin);
            if (*it == *bit) continue;
            return *it < *bit;
        }
        return false;
    }
    return true;
}

#include <iostream>

int main() {
    string a = "11111", b = "11110";
    std::cout << std::boolalpha << le(a.cbegin(), a.cend(), b.cbegin(), b.cend());
}
