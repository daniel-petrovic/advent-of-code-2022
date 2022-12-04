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

        auto contains = (a <= c && d <= b) || (c <= a && b <= d);
        cnt += contains;

        cout << contains << '\n';
    }

    cout << cnt << endl;
}