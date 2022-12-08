#include <bits/stdc++.h>
using namespace std;

vector<vector<bool>> vis;
vector<string> h;
size_t M, N;

void walk_left(int row)
{
    char mx = h[row][0];
    for (size_t col = 1; col < N; ++col) {
        if (mx < h[row][col]) {
            vis[row][col] = true;
            mx = h[row][col];
        }
    }
}

void walk_right(int row)
{
    char mx = h[row][N-1];
    for (int col = N-2; col > 0; --col) {
        if (mx < h[row][col]) {
            vis[row][col] = true;
            mx = h[row][col];
        }
    }
}

void walk_top(int col)
{
    char mx = h[0][col];
    for (size_t row = 1; row < M; ++row) {
        if (mx < h[row][col]) {
            vis[row][col] = true;
            mx = h[row][col];
        }
    }
}

void walk_bottom(int col)
{
    char mx = h[M-1][col];
    for (int row = M-2; row > 0; --row) {
        if (mx < h[row][col]) {
            vis[row][col] = true;
            mx = h[row][col];
        }
    }
}

int main()
{
    string line;
    while (getline(cin, line)) {
        h.push_back(line);
    }

    M = h.size();
    N = h.front().size();

    vis.resize(M, vector<bool>(N));

    for (size_t row = 0; row < M; ++row) {
        vis[row][0] = vis[row][N-1] = true;
    }

    for (size_t col = 0; col < N; ++col) {
        vis[0][col] = vis[N-1][col] = true;
    }

    for (size_t row = 0; row < vis.size(); ++row) {
        walk_left(row);
        walk_right(row);
    }

    for (size_t col = 0; col < vis.front().size(); ++col) {
        walk_top(col);
        walk_bottom(col);
    }

    size_t count{};
    for (size_t i = 0; i < M; ++i) 
        for (size_t j = 0; j < N; ++j)
            count += vis[i][j];

    cout << "count = " << count << endl;
}
