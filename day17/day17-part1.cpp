#include <bits/stdc++.h>
using namespace std;

using pii = pair<int,int>;
using vpii = vector<pii>;

using Shape = vpii;


struct Box {
    int x{}; // x of bottom left
    int y{}; // y of bottom left
    int w{}; // width
    int h{}; // height

    int left() const noexcept { return x;};
    int right() const noexcept { return x + w - 1; }
    int top() const noexcept { return y + h -1; }
    int bottom() const noexcept { return y; }
};

struct Rock {
    Rock() = default;
    Rock(Shape s) {
        shape = std::move(s);
        int xmin = INT_MAX;
        int xmax = 0;
        int ymin = INT_MAX; 
        int ymax = 0;
        for (auto [x,y] : shape)
        {
            xmin = min(xmin, x);
            xmax = max(xmax, x);
            ymin = min(ymin, y);
            ymax = max(ymax, y );
        }

        box.w = xmax - xmin + 1;
        box.h = ymax - ymin + 1;
    }
    Shape shape;
    Box box;
};

/* y
 * ^
 * |
 * |
 * |
 * |
 * +-----------> x
     

*/

// #### y==0
Shape S1 = { {0, 0}, {1, 0}, {2, 0}, {3, 0} };

//       .#. y==2
//       ### y==1
//       .#. y==0
// x     012
Shape S2 = {
        {1, 2},
        {0, 1}, {1, 1}, {2, 1},
        {1, 0}};

//       ..# y==2
//       ..# y==1
//       ### y==0
// x     012
Shape S3 = {
    {2,2},
    {2,1},
    {0,0}, {1,0}, {2,0}
};

//  # y==3
//  #
//  #
//  # y==0
//x 0
Shape S4 = {
    {0,3},{0,2},{0,1},{0,0}
};

//  ## y==1
//  ## y==0
//x 01
Shape S5 = {
    {0,1},{1,1},
    {0,0},{1,0}
};


bool can_push_to(int x0, int y0, const Rock& f);
void push(int x0, int y0, Rock& f);

static constexpr int XMAX = 7; 
static constexpr int YMAX = 10'000;
bool occupied[YMAX][XMAX];


int main()
{
    for (int j = 0; j < YMAX; ++j) {
        for (int i = 0; i < XMAX; ++i)
            occupied[j][i] = false;
        }

    auto rocks = array {Rock{S1}, Rock{S2}, Rock{S3}, Rock{S4}, Rock{S5}};

    auto commands = string(istream_iterator<char>{cin}, istream_iterator<char>{});

    auto draw = [&] {
        const auto Y = 20;
        cout << endl;
        for (int y = Y; y >= 0; --y) {
            for (int x = 0; x < XMAX; ++x) {
                char c = occupied[y][x] ? '#' : '.';
                cout << c;
            }
            cout << endl;
        }
        cout << endl;
    };

    Rock rock;

    for (int i=0, j=0, x0=2, y0=3; i<2022; ++i, y0 = rock.box.top() + 4)
    {
        //printf("rock %d starts fallinig at (%d, %d)\n", i, x0, y0);
        rock = rocks[i%5];
        rock.box.x = x0;
        rock.box.y = y0;

        for (int x=x0, y=y0;;) {

            if (commands[j] != '>' and commands[j] != '<') {
                throw "invalid command";
            }

            auto x2 = x + ((commands[j] == '>') ? 1 : -1);
            j = (j + 1) % commands.size();
            //cout << "\t" << " '" << commands[j] << "' ";

            if (can_push_to(x2, y, rock)) {
                push(x2, y, rock);
                x = x2;
                //draw();
            }

            auto y2 = y-1;

            if (can_push_to(x, y2, rock)) {
                push(x, y2, rock);
                y = y2;
                //draw();
            }
            else {
                //printf("\t: rock %d : cannot push down to y2=%d\n", i, y2);
                break;
            }
        }
    } 

    //draw();

    cout << "height = " << rock.box.top() + 1  << endl;
}

bool can_push_to(int x0, int y0, const Rock& f)
{
    if (x0 < 0) return false;
    if (x0 + f.box.w > XMAX) return false;
    if (y0 < 0) return false;


    for (auto [xp,yp] : f.shape) {

        xp += x0;
        yp += y0;

        bool new_xy = true;

        for (auto [xx, yy] : f.shape) {
            if (xp == f.box.x + xx and yp == f.box.y + yy) {
                new_xy = false;
                break;
            }
        }

        if (new_xy and occupied[yp][xp])
            return false;
    }

    return  true;
}

void push(int x0, int y0, Rock& f)
{
    if (x0 == f.box.x and y0 == f.box.y)
        return;

    //printf("\t pushing rock to (x0,y0)=(%d,%d)\n", x0, y0);

    for (auto [xp, yp] : f.shape) {
        auto x = f.box.x + xp;
        auto y = f.box.y + yp;
        occupied[y][x] = false;
    }

    f.box.x = x0;
    f.box.y = y0;

    for (auto [xp, yp] : f.shape) {
        auto x = f.box.x + xp;
        auto y = f.box.y + yp;
        occupied[y][x] = true;
    }
}
