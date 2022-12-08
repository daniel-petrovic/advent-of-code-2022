#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> x;
vector<string> h;
size_t M, N;

int main()
{
    string line;
    while (getline(cin, line))
    {
        h.push_back(line);
    }

    M = h.size();
    N = h.front().size();

    int score = 0;

    for (int i = 1; i < M - 1; ++i)
    {
        for (int j = 1; j < N - 1; ++j)
        {
            auto cur = h[i][j];
            int k = 0;
            // left
            int left = 1;
            k = j - 2;
            if (h[i][j - 1] < cur)
            {
                for (; k >= 0 && h[i][k] < cur; --k)
                    ++left;
            }
            for (; k >= 0 && h[i][k] > h[i][k + 1]; --k)
                ++left;

            // right
            int right = 1;
            k = j + 2;
            if (h[i][j + 1] < cur)
            {
                for (; k < N && h[i][k] < cur; ++k)
                    ++right;
            }
            for (; k < N && h[i][k] > h[i][k - 1]; ++k)
                ++right;

            // top
            int top = 1;
            k = i - 2;
            if (h[i - 1][j] < cur)
            {
                for (; k >= 0 && h[k][j] < cur; --k)
                    ++top;
            }
            for (; k >= 0 && h[k][j] > h[k + 1][j]; --k)
                ++top;

            // bottom
            int bottom = 1;
            k = i + 2;
            if (h[i + 1][j] < cur)
            {
                for (; k < M && h[k][j] < cur; ++k)
                    ++bottom;
            }
            for (; k < M && h[k][j] > h[k - 1][j]; ++k)
                ++bottom;

            score = max(score, left * right * top * bottom);
        }
    }

    cout << "score = " << score << endl;
}
