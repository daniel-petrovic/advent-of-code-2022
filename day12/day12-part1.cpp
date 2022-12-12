#include <bits/stdc++.h>
using namespace std;

vector<string> grid;
vector<vector<int>> d;
vector<vector<bool>> vis;
int M, N;

void bfs(int i, int j);

int main()
{
    string line;
    while (getline(cin, line)) {
        grid.push_back(line);
    }

    M = grid.size();
    N = grid.front().size();

    d.resize(M, vector<int>(N, -1));
    vis.resize(M, vector<bool>(N));

    int iS{-1}, jS{-1};
    int iE{-1}, jE{-1};
    for (int i = 0; i < M; ++i)
        for (int j = 0; j < N; ++j)
        {
            if (grid[i][j] == 'S') {
                iS = i;
                jS = j;
            }

            if (grid[i][j] == 'E') {
                iE = i;
                jE = j;
            }
        }

    grid[iS][jS] = 'a';
    grid[iE][jE] = 'z';

    bfs(iS, jS);

    printf("d[E] = %d steps\n", d[iE][jE]);
}

void bfs(int istart, int jstart)
{
    using pii = pair<int,int>;
    using vii = vector<pii>;

    queue<pii> q;
    q.emplace(istart, jstart);
    d[istart][jstart] = 0;

    while (!q.empty()) {
        auto [i, j ] = q.front();
        q.pop();

        if (vis[i][j]) continue;
        vis[i][j] = true;

        for (pii dxy  : vii{{0,1},{0,-1},{1,0},{-1,0}})
        {
            auto [di, dj] = dxy;
            auto x = i + di;
            auto y = j + dj;

            if (x < 0 || x >= M) continue;
            if (y < 0 || y >= N) continue;

            if (grid[x][y] > grid[i][j] + 1) continue;

            if (vis[x][y]) continue;

            d[x][y] = d[i][j] + 1;
            q.emplace(x, y);
        }
    }
}
