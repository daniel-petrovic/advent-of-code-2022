#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;
using vii = vector<pii>;
using vvii = vector<vii>;
using vs = vector<string>;

int M, N;
int MS, NS;

vvii read_wall();
vs draw_wall(const vvii &wall);
int simfall(vs& wall);

int main()
{
    auto wall = draw_wall(read_wall());

    printf("M, N = %d, %d\n", M, N);
    printf("MS, NS = %d, %d\n", MS, NS);

    auto num = simfall(wall);

    for (string_view row : wall)
    {
        cout << row << endl;
    }

    cout << endl;
    cout << "num = " << num  << endl;
}

vvii read_wall()
{
    MS = 0, NS = 500;

    int xmin = NS;
    int xmax = NS;
    int ymin = MS;
    int ymax = MS;

    vvii wall;

    string line;
    while (getline(cin, line))
    {
        istringstream is(line);
        vii rocks;

        int x, y;
        char comma;

        while (is >> x >> comma >> y)
        {
            string arrow;
            is >> arrow;
            rocks.emplace_back(x, y);

            xmin = min(xmin, x);
            xmax = max(xmax, x);
            ymin = min(ymin, y);
            ymax = max(ymax, y);
        }

        wall.push_back(rocks);
    }

    for (auto &rocks : wall)
        for (auto &r : rocks)
        {
            r.first -= xmin;
            r.second -= ymin;
        }

    M = ymax - ymin + 1;
    N = xmax - xmin + 1;

    MS = 0 - ymin;
    NS = 500 - xmin;

    return wall;
}

vs draw_wall(const vvii &wall)
{
    vs ret(M, string(N, '.'));
    ret[MS][NS] = '+';

    for (const auto &rocks : wall)
    {

        auto [x0, y0] = rocks.front();
        ret[y0][x0] = '#';

        for (int i = 1; i < rocks.size(); ++i)
        {
            // x0 .. x .. x1 dx > 0
            // x1 .. x .. x0 dx < 0
            auto [x1, y1] = rocks[i];
            auto dx = x1 - x0;
            auto dy = y1 - y0;
            if (dy == 0)
                for (int step = (dx < 0) - (dx > 0); dx != 0; dx += step)
                    ret[y0][x0 + dx] = '#';

            if (dx == 0)
                for (int step = (dy < 0) - (dy > 0); dy != 0; dy += step)
                    ret[y0 + dy][x0] = '#';

            x0 = x1, y0 = y1;
        }
    }
    return ret;
}

int simfall(vs& wall) {
    int ret = 0;

    auto pos_ok = [](int m, int n) {
        return m >= 0 && m < M && n >= 0 && n < N;
    };

    while (true) {
        int i = MS, j = NS;
        bool can_move;

        do {
            if (pos_ok(i+1, j) && wall[i+1][j] == '.')
            {
                can_move = true;
                ++i;
            }
            else if (pos_ok(i+1, j-1) && wall[i+1][j-1] == '.') {
                can_move = true;
                ++i, --j;
            }
            else if (pos_ok(i+1, j+1) && wall[i+1][j+1] == '.') {
                can_move = true;
                ++i, ++j;
            }
            else {
                can_move = false;
            }
        } while (can_move and j > 0 and j < N-1 and i < M-1);

        if (i == MS && j == NS) 
            break;

        if (i >= M-1 || j == 0 || j >= N-1)
            break;

        wall[i][j] = 'o';
        ++ret;
    }

    return ret;
}