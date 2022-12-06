#include <bits/stdc++.h>
using namespace std;

int main() {
  string s;
  getline(cin, s);

  unsigned i = 3;
  bool is_unique;
  for (; !is_unique && i < s.size(); ++i) {
    // i, i-1, i-2, i-3
    set<char> x;
    bool isq = true;
    for (auto j = i - 3; j <= i; ++j) {
      isq &= x.insert(s[j]).second;
    }

    is_unique = isq;
  }

  cout << i << endl;
}
