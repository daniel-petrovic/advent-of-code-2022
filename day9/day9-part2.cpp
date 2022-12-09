#include <bits/stdc++.h>

using namespace std;

int main()
{
    using pii = pair<int, int>;
    set<pii> vis;

    array<pii, 10> xy{}; // 0 == HEAD, back() == TAIL
    vis.emplace(0, 0);

    char dir;
    int steps;

    while (cin >> dir >> steps)
    {
        cin.ignore(1000, '\n');

        int xsign = (dir == 'R') - (dir == 'L');
        int ysign = (dir == 'U') - (dir == 'D');
        int dx = xsign * steps;
        int dy = ysign * steps;

        auto check_move = [](int &xt, int &yt, int x, int y)
        {
            if (x - xt >= 2)
            {
                ++xt;
                if (y - yt >= 2)
                    ++yt;
                else if (yt - y >= 2)
                    --yt;
                else
                    yt = y;
            }
            if (xt - x >= 2)
            {
                --xt;
                if (y - yt >= 2)
                    ++yt;
                else if (yt - y >= 2)
                    --yt;
                else
                    yt = y;
            }
            if (y - yt >= 2)
            {
                ++yt;

                if (x - xt >= 2)
                    ++xt;
                else if (xt - x >= 2)
                    --xt;
                else
                    xt = x;
            }
            if (yt - y >= 2)
            {
                --yt;
                if (x - xt >= 2)
                    ++xt;
                else if (xt - x >= 2)
                    --xt;
                else
                    xt = x;
            }
        };

        for (; dx != 0; dx -= xsign)
        {
            xy[0].first += xsign;
            for (int i = 1; i < xy.size(); ++i)
            {
                check_move(xy[i].first, xy[i].second, xy[i - 1].first, xy[i - 1].second);
            }
            vis.insert(xy.back());
        }

        for (; dy != 0; dy -= ysign)
        {
            xy[0].second += ysign;
            for (int i = 1; i < xy.size(); ++i)
            {
                check_move(xy[i].first, xy[i].second, xy[i - 1].first, xy[i - 1].second);
            }
            vis.insert(xy.back());
        }
    }

    cout << vis.size() << endl;
}