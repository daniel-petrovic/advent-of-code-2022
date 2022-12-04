#include <array>
#include <iostream>

using namespace std;

int main()
{
    unsigned cnt{0};

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

        auto overlapp = (c <= b && b <= d) || (a <= d && d <= b);
        cnt += overlapp;

        cout << overlapp << '\n';
    }

    cout << cnt << endl;
}