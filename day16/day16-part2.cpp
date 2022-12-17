#include <bits/stdc++.h>
using namespace std;

int V;
map<string, int> Vindex;
vector<vector<int>> adj;
vector<int> F; // flow;
               //
static constexpr unsigned NUM_NONZERO_NODES = 32768; // 2**15
static constexpr unsigned TIME_MAX = 30;
static constexpr unsigned NODES_MAX = 54; // from input

int memo[NUM_NONZERO_NODES][NODES_MAX][TIME_MAX+1][2];

void read_graph();
int solve(int u, uint64_t opened, int time_left, bool elephant, int debug_level);

int main()
{
    for (int i1 = 0; i1 < NUM_NONZERO_NODES; ++i1)
        for (int i2 = 0; i2 < NODES_MAX; ++i2)
            for (int i3 = 0; i3 < TIME_MAX+1; ++i3)
                for (int i4 = 0; i4 < 2; ++i4)
                    memo[i1][i2][i3][i4] = -1;
    
    read_graph();
    int cnt_zero = 0;
    for (auto v : Vindex) {
        cout << v.first << " = " << v.second << " flow rate = " << F[v.second] << endl;
        if (F[v.second] == 0) ++cnt_zero;
    }

    cout << cnt_zero << " nodes with flow == 0\n";
    cout << V-cnt_zero << " nodes with flow > 0\n";

    uint64_t  opened = 0;
    int debug_level = 0;
    bool elephant = true;
    auto flow = solve(Vindex["AA"], opened, 26, elephant, debug_level);
    cout << "flow = " << flow << endl;
}

int solve(int u, uint64_t opened, int time_left, bool elephant, int debug_level)
{
    if (time_left == 0) // becuse open takes 1min
        return elephant ? solve(Vindex["AA"], opened, 26, not elephant, 0) : 0;

    auto& mem = memo[opened][u][time_left][elephant];
    if (mem >= 0)
    {
        return mem;
    }

    int m = 0;

    if (F[u] > 0 and (opened & (1LL<<u)) == 0) {
        auto df = F[u]*(time_left-1);
        auto s = df + solve(u, opened | (1LL<<u), time_left-1, elephant, debug_level+1);
        m = max(m, s);
    }

    for (auto v : adj[u]) {
        auto s = solve(v, opened, time_left-1, elephant, debug_level+1);
        m = max(m, s);
    }


    mem = m;
    return m;
}

void read_graph()
{
    map<string, vector<string>> Gs;
    unordered_map<string, int> Flow;
    vector<pair<string, int>> names;

    while (true)
    {
        char valve[3];
        int flow_rate;
        char valves[256];

        if (scanf("Valve %s has flow rate=%d; %*s %*s to %*s %[^\n]\ns", valve, &flow_rate, valves) != 3)
            break;

        string v = valve;
        Flow[valve] = flow_rate;
        names.emplace_back(valve, flow_rate);

        vector<string> adj;
        for (const char* p = valves; *p != '\0';)
        {
            while (*p == ' ' || *p == ',') ++p;
            auto q = p;
            while (*p != ' ' && *p != ',' && *p != '\0') ++p;
            adj.emplace_back(q, p);
        }

        Gs[v] = adj;
    }

    sort(names.begin(), names.end(), [](auto p1, auto p2) {
            return p1.second > p2.second;
            });

    for (unsigned i = 0; i < names.size(); ++i)
        Vindex[names[i].first] = i;

    V = Gs.size();
    adj.resize(V);
    F.resize(V);

    for (const auto& u : Gs) {
        cout << u.first << endl;
        auto ui = Vindex[u.first];
        F[ui] = Flow[u.first];

        for (const auto& v : u.second) {
            cout << "\t-> " << v << endl;
            auto vi = Vindex[v];
            adj[ui].push_back(vi);
        }
    }
}
