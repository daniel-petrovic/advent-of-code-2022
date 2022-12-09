#include <bits/stdc++.h>

using namespace std;

int main()
{
    int x{}, y{}, xt{}, yt{};
    set<pair<int,int>> vis;

    char dir;
    int steps;

    x = y = xt = yt = 0;
    vis.emplace(xt,yt);

    while (cin >> dir >> steps) {
        cin.ignore(1000, '\n');
        int xsign = (dir=='R')-(dir=='L');
        int ysign = (dir=='U')-(dir=='D');
        int dx = xsign * steps;
        int dy = ysign * steps;

        auto check_move = [&]() {
            auto xo = xt;
            auto yo = yt;
            if (x-xt >=2 ) {
                ++xt;
                if (abs(y-yt) >= 1) {
                    yt = y;
                }
            }

            if (xt-x >= 2) {
                --xt;
                if (abs(y-yt) >= 1) {
                    yt = y;
                }
            }

            if (y-yt >= 2) {
                ++yt;
                if (abs(x-xt) >= 1) {
                    xt = x;
                }
            }

            if (yt-y >= 2) {
                --yt;
                if (abs(x-xt) >= 1) {
                    xt = x;
                }
            }

            if (xo != xt || yo != yt) 
                vis.emplace(xt, yt);
        };

        for(; dx != 0; dx -= xsign) {
            x += xsign;
            check_move();
        }

        for (; dy != 0; dy -= ysign) {
            y += ysign;
            check_move();
        }
    }

    cout << vis.size() << endl;
}