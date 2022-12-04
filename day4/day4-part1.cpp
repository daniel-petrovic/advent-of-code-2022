#include <array>
#include <iostream>

using namespace std;

int main()
{
    unsigned cnt;

    while (true)
    {
        int a,b,c,d;
        cin >> a;
        cin.get();
        cin >> b;
        cin.get();
        cin >> c;
        cin.get();
        cin >> d;

        if (!cin) {
            break;
        }

        cout << a << "-" << b << "," << c << "-" << d << " : ";

        using pii = pair<int,int>;
        auto p = array {pii{a,b}, pii{c,d}};

        auto contains = false;
        for (auto i : {0,1})
        {
            auto [x, y] = p[i];
            auto [v, z] = p[1-i];

            if (x <= v && z <= y) {
                contains = true;
                ++cnt;
                break;
            }
        }
        cout << contains << '\n';
    }

    cout << cnt << endl;
}