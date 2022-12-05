#include <bits/stdc++.h>
using namespace std;

size_t N;
vector<string> stacks;

void move(int count, int from, int to)
{
    stacks[to] += string((stacks[from].rbegin()+count).base(), stacks[from].end());
    stacks[from].resize(stacks[from].size() - count);
}

int main()
{
    string l;
    vector<string> lines;

    while (getline(cin, l) && !l.empty())
    {
        int i = 0;
        string line;

        while (i < l.size())
        {
            if (l[i] == '[')
            {
                line += l[i + 1];
            }
            else
            {
                line += ' ';
            }
            i += 4;
        }
        lines.push_back(line);
    }

    N = lines.front().size();
    cout << "N = " << N << endl;

    stacks.resize(N);

    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < lines.size(); ++j)
            stacks[i] += lines[j][i];
    }

    for (auto &s : stacks)
    {
        s = string(s.rbegin(), s.rend());
        s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch)
                             { return !std::isspace(ch); })
                    .base(),
                s.end());
        s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch)
                                        { return !std::isspace(ch); }));
        cout << "'" << s << "'" << endl;
    }

    while (getline(cin, l))
    {
        stringstream ss(l);

        string command;
        int count;
        int from;
        int to;

        ss >> command >> count >> command >> from >> command >> to;
        move(count, from - 1, to - 1);
    }

    for (const auto &s : stacks)
        cout << s.back();
    cout << endl;
}