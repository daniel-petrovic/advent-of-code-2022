#include <bits/stdc++.h>

using namespace std;

int main()
{
    string inst;
    int val;
    int cycle{};

    int score{};
    int x = 1;

    while (cin >> inst) {
        ++cycle;
        if (cycle == 20 || cycle == 60 || cycle ==  100 || cycle == 140 || cycle == 180 || cycle == 220)
        {
            score += cycle * x;
        }
        cout << inst << " ";
        if (inst == "noop") {
            cout << endl;
            continue;
        }
        cin >> val;
        cout << val << endl;
        ++cycle;
        x += val;
    }

    cout << score << endl;
}