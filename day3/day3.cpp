#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main()
{
    auto calc_prio = [](char c) {
        if ('a' <= c && c <= 'z') {
            return 1 + c-'a';
        }
        else {
            return 27 + c - 'A';
        }
    };

    string line1, line2, line3;
    ll prio = 0;

    while (getline(cin, line1)&&getline(cin, line2)&&getline(cin, line3)) {
        ranges::sort(line1);
        ranges::sort(line2);
        ranges::sort(line3);

        vector<char> intersection_12;
        vector<char> intersection;

        ranges::set_intersection(line1, line2, back_inserter(intersection_12));
        ranges::set_intersection(intersection_12, line3, back_inserter(intersection));

        prio += calc_prio(intersection[0]);
    }

    cout << prio << endl;
}