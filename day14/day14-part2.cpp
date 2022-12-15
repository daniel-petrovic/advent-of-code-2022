#include <bits/stdc++.h>
using namespace std;

struct hash_pair
{
    template <class T>
    static void hash_combine(size_t &seed, const T &t)
    {
        seed ^= std::hash<T>()(t) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    }

    template <class T1, class T2>
    size_t operator()(const pair<T1, T2> &p) const
    {
        size_t seed = 0;
        hash_combine(seed, p.first);
        hash_combine(seed, p.second);
        return seed;
    }
};

using pii = pair<int, int>;
using vii = vector<pii>;
using vvii = vector<vii>;
using sii = unordered_set<pii, hash_pair>;

int ymax = 0;
const int xs = 500;
const int ys = 0;

sii rocks;
sii sand;

pii simfall();
sii read_rocks();

int main()
{
    rocks = read_rocks();
    cout << "ymax = " << ymax << endl;

    while (true)
    {
        auto [x, y] = simfall();
        if (x == xs && y == ys)
            break;
        sand.emplace(x, y);
    }

    cout << "count = " << sand.size()+1 << endl; // +1 for the start sand unit (xs,ys)
}

pii simfall()
{
    int x = xs;
    int y = ys;

    while (true)
    {
        bool moved = false;
        // printf ("(x,y) = (%d,%d)\n", x, y);

        for (auto [dx, dy] : vii{{0, 1}, {-1, 1}, {1, 1}})
        {
            auto xx = x + dx;
            auto yy = y + dy;

            if (!rocks.contains({xx, yy}) && !sand.contains({xx, yy}))
            {
                x = xx, y = yy;
                moved = true;
                break;
            }
        }

        if (!moved)
            break;

        if (y == ymax - 1)
            break;
    }

    return {x, y};
}

sii read_rocks()
{
    string line;
    vvii lines;

    while (getline(cin, line))
    {
        istringstream is(line);

        vii points;

        int x, y;
        char comma;
        while (is >> x >> comma >> y)
        {
            string arrow;
            is >> arrow;
            points.emplace_back(x, y);
            ymax = max(ymax, y);
        }
        lines.push_back(points);
    }

    ymax += 2;

    sii r;
    for (auto points : lines)
    {

        auto [x0, y0] = points.front();
        r.emplace(x0, y0);

        for (unsigned i = 1; i < points.size(); ++i)
        {
            auto [x1, y1] = points[i];
            int dx = x1 - x0;
            int dy = y1 - y0;

            if (dy == 0)
                for (int step = (dx < 0) - (dx > 0); dx != 0; dx += step)
                    r.emplace(x0 + dx, y0);

            if (dx == 0)
                for (int step = (dy < 0) - (dy > 0); dy != 0; dy += step)
                    r.emplace(x0, y0 + dy);

            x0 = x1, y0 = y1;
        }
    }

    return r;
}
