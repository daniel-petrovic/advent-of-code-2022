#include <bits/stdc++.h>

using namespace std;

int main()
{
    string inst;
    int val;
    int cycle{};

    int score{};
    int x = 1;

    auto draw = [](int& cyc, int xx)
    {
        auto pos = cyc - 1;
        if (xx - 1 <= pos && pos <= xx + 1)
            cout << '#';
        else
            cout << '.';

        if (cyc == 40)
        {
            cout << '\n';
            cyc = 0;
        }
    };

    while (true)
    {

        if (!(cin >> inst))
            break;

        ++cycle;
        draw(cycle, x);

        if (inst == "noop")
        {
            continue;
        }
        else
        {
            if (!(cin >> val))
                break;
            ++cycle;
            draw(cycle, x);
            x += val;
        }
    }
    cout << endl;
}