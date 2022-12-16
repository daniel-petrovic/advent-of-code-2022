#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using pii = pair<int, int>;
using vpii = vector<pii>;
using apii = array<pii, 2>;
using vapii = vector<apii>;

template <typename T>
void hash_combine(size_t& seed, const T& v)
{
    seed ^= std::hash<T>()(v) + 0x955371 + (seed << 6) + (seed >> 2);
}

struct hash_pair {
    template <typename T1, typename T2>
    size_t operator()(const std::pair<T1,T2>& p) const {
        size_t seed = 0;
        hash_combine(seed, p.first);
        hash_combine(seed, p.second);
        return seed;
    }
};

ll calc_union(vpii ranges);
vpii calc_ranges(const vapii &sensors, const int Y);
vapii read_sensors();

int main()
{
    static constexpr int Y = 2000000;
    
    auto sensors = read_sensors();
    auto rngs = calc_ranges(sensors, Y);
    auto count = calc_union(rngs);

    unordered_set<pii, hash_pair> existing_beacons;

    for (auto sensor : sensors)
    {
        const auto [xb, yb] = sensor[1]; // beacon

        if (yb != Y) continue;
        
        // yb == Y:
        for (auto [l, r]: rngs)
            if (l <= xb && xb <= r) {
                existing_beacons.emplace(xb, yb);
                break;
            }
    }

    count -= existing_beacons.size();

    cout << "count = " << count << endl;
}

ll range_length(pii r)
{
    assert(r.first < r.second);
    return r.second - r.first + 1LL;
}

ll calc_union(vpii rngs)
{
    if (rngs.empty())
        return 0;

    sort(rngs.begin(), rngs.end(), [](auto p1, auto p2)
         { return p1.first < p2.first; });

    int l = rngs[0].first;
    int r = rngs[0].second;
    auto ret = range_length(rngs[0]);

    for (unsigned i = 1; i < rngs.size(); ++i)
    {
        assert(l < r);
        auto [l2, r2] = rngs[i];

        if (l2 <= r)
        {
            if (r2 <= r)
            {
                continue;
            }
            else
            {
                ret += r2 - r;
                r = r2;
            }
        }
        else
        {
            ret += range_length(rngs[i]);
            l = l2, r = r2;
        }
    }

    return ret;
}

optional<pii> calc_sensor_range(const apii &sensor, const int Y)
{
    const auto &S = sensor[0];
    const auto &B = sensor[1];
    const auto dx = abs(S.first - B.first);
    const auto dy = abs(S.second - B.second);

    auto xS = S.first;
    const auto dl = (dx + dy) - abs(S.second - Y); //   -dl <---- x ---> dl
    if (dl < 0)
    {
        return nullopt;
    }

    return pii{xS - dl, xS + dl}; // num of points = (xS+dl) - (xS-dl) + 1 = 2*dl + 1
}

vpii calc_ranges(const vapii &sensors, const int Y)
{
    vpii ret;
    for (auto sensor : sensors)
    {
        auto r = calc_sensor_range(sensor, Y);
        if (!r.has_value())
            continue;
        ret.push_back(r.value());
    }
    return ret;
}

vapii read_sensors()
{
    vapii ret;
    while (cin)
    {
        int xs, ys, xb, yb;
        while (cin && (cin.get() != 'x' || cin.get() != '='))
            ;
        cin >> xs;
        while (cin && (cin.get() != 'y' || cin.get() != '='))
            ;
        cin >> ys;
        while (cin && (cin.get() != 'x' || cin.get() != '='))
            ;
        cin >> xb;
        while (cin && (cin.get() != 'y' || cin.get() != '='))
            ;
        cin >> yb;
        if (cin)
        {
            ret.push_back(apii{{{xs, ys}, {xb, yb}}});
        }
    }

    return ret;
}