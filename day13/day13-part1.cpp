#include <bits/stdc++.h>
using namespace std;

bool in_order(std::string l1, std::string l2);

int main() {
  string l1, l2;
  int index{}, sum{};

  while (getline(cin, l1) && getline(cin, l2)) {
    cin.ignore(1000, '\n');
    cout << l1 << endl << l2 << endl << endl;
    ++index;
    if (in_order(l1, l2)) {
      sum += index;
    }
  }

  cout << "sum = " << sum << endl;
}

void trim_one(string &s, char cf) {
  if (!s.empty() && s.front() == cf) {
    s.erase(0, 1);
  }
}

void trim_one(string &s, char cf, char cb) {
  if (!s.empty() && s.front() == cf && s.back() == cb) {
    s.erase(0, 1);
    s.erase(s.size() - 1, 1);
  }
}

struct head {
  string h;
};

head consume_head(string &x) {
  trim_one(x, '[', ']');
  trim_one(x, ',');

  if (x.empty()) {
    return {};
  }

  head h;
  if (isdigit(x.front())) {
    auto it = find_if(x.begin(), x.end(), [](char c) { return !isdigit(c); });
    h.h = string(x.begin(), it);
    x.erase(x.begin(), it);

    return h;

  } else if (x.front() == '[') {
    int pos = 0;
    int cnt = 0;
    do {
      if (x[pos] == '[')
        ++cnt;
      if (x[pos] == ']')
        --cnt;
      ++pos;
    } while (pos < x.size() && cnt != 0);
    h.h = x.substr(0, pos);
    x.erase(0, pos);
  } else {
    throw "invalid format exception";
  }

  return h;
}

int compare(int a, int b) {
  if (a < b)
    return -1;
  if (a > b)
    return 1;
  return 0;
}

int compare(head h1, head h2);

int compare(std::string l1, std::string l2) {
  int cmp = 0;
  while ((cmp = compare(consume_head(l1), consume_head(l2))) == 0 &&
         (!l1.empty() || !l2.empty()))
    ;
  return cmp;
}

int compare(head h1, head h2) {

  cout << '\t' << string(80, '<') << endl;
  cout << '\t' << "h1: '" << h1.h << "'" << endl;
  cout << '\t' << "h2: '" << h2.h << "'" << endl;
  cout << '\t' << string(80, '<') << endl;

  if (h1.h.empty()) {
    return h2.h.empty() ? 0 : -1;
  }

  if (h2.h.empty()) {
    return 1;
  }

  if (h1.h.front() != '[' && h2.h.front() != '[') {
    return compare(stoi(h1.h), stoi(h2.h));
  } else if (h1.h.front() == '[' && h2.h.front() == '[') {
    return compare(h1.h, h2.h);
  } else if (h1.h.front() == '[') {
    return compare(h1.h, '[' + h2.h + ']');
  } else {
    return compare('[' + h1.h + ']', h2.h);
  }
}

bool in_order(std::string l1, std::string l2) { return compare(l1, l2) == -1; }
