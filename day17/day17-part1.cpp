#include <bits/stdc++.h>
using namespace std;
using namespace std::literals;

static constexpr int YMAX = 5000;
static constexpr int XMAX = 7;
char grid[YMAX][XMAX];

/* y
 * ^
 * |
 * |
 * |
 * +--------> x
 */

void draw_grid(const int y)
{
    cout << endl;
    for (int yy = y; yy >= 0; --yy) {
        for (int xx = 0; xx < XMAX; ++xx)
            cout << grid[yy][xx];
        cout << endl;
    }
    cout << endl;
}

constexpr int height(string_view shape)
{
    int ret = 0;
    for (auto c : shape) 
        ret += c == '\n';
    return ret + 1;
}

constexpr int width(string_view shape)
{
    return find(shape.begin(), shape.end(), '\n') - shape.begin();
}

int main()
{
    for (int i = 0; i < YMAX; ++i)
        for (int j = 0; j < XMAX; ++j)
            grid[i][j] = '.';
    
    constexpr auto shapes = array {
        "####"sv,

        ".#.\n"
        "###\n"
        ".#."sv,

        "..#\n"
        "..#\n"
        "###"sv,

        "#\n"
        "#\n"
        "#\n"
        "#"sv,

        "##\n"
        "##"sv
    };

    //draw_grid(20);

    static constexpr auto heights = array {
        height(shapes[0]),
        height(shapes[1]),
        height(shapes[2]),
        height(shapes[3]),
        height(shapes[4]),
    };

    static constexpr auto widths = array {
        width(shapes[0]),
        width(shapes[1]),
        width(shapes[2]),
        width(shapes[3]),
        width(shapes[4]),
    };

    cout << "heights: ";
    for (auto h : heights) cout << h << " ";
    cout << endl;

    cout << "widths: ";
    for (auto w : widths) cout << w << " ";
    cout << endl;

    static_assert(shapes.size() == 5);

    const auto commands = string(istream_iterator<char>(cin), istream_iterator<char>());
    cout << "command: " << commands << endl;


    auto can_move_to = [](int x0, int y0, string_view shape, int w, int h) {

        if (x0 < 0) return false;
        if (y0 < 0) return false;
        if (x0 + w > XMAX) return false;

        for (int i = 0; i < h; ++i)
            for (int j = 0; j < w; ++j)
            {
                if (shape[i*(w+1) + j] == '#')
                    if (grid[h-i-1+y0][j + x0] == '#')
                        return false;
            }

        return true;
    };

    auto rest = [](int x0, int y0, string_view shape, int w, int h) {

        for (int i = 0; i < h; ++i)
            for (int j = 0; j < w; ++j)
            {
                if (shape[i*(w+1) + j] == '#')
                    grid[h-i-1+y0][j + x0] = '#';
            }

        return true;
    };

    int ystart = 3;
    int cmd = 0;
    int hmax = 0;

    for (int counter = 0; counter < 2022; ++counter) {
        int i = counter % shapes.size();
        const auto shape = shapes[i];
        const auto h = height(shape);
        const auto w = width(shape);
        
        int x = 2;
        int y = ystart;

        while (true) {
            char c = commands[cmd];
            cmd = (cmd + 1) % commands.size();

            if (c == '>' and can_move_to(x+1, y, shape, w, h)) {
                ++x;
            }

            if (c == '<' and can_move_to(x-1, y, shape, w, h)) {
                --x;
            }

            if (can_move_to(x, y-1, shape, w, h)) {
                --y;
            }
            else {
                hmax = max(hmax, y+h);
                ystart = hmax + 3;
                rest(x, y, shape, w, h);
                break;
            }
        }
    }

    draw_grid(20);

    cout << "height: " << hmax  << endl;
}
