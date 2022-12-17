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

int memo[NUM_NONZERO_NODES][NODES_MAX][TIME_MAX+1];

void read_graph();
int solve(int u, uint64_t opened, int time_left, int flow);

int main()
{
    read_graph();
    int cnt_zero = 0;
    for (auto v : Vindex) {
        cout << v.first << " = " << v.second << " flow rate = " << F[v.second] << endl;
        if (F[v.second] == 0) ++cnt_zero;
    }

    cout << cnt_zero << " nodes with flow == 0\n";
    cout << V-cnt_zero << " nodes with flow > 0\n";

    uint64_t  opened = 0;
    auto flow = solve(Vindex["AA"], opened, 30, 0);
    cout << "flow = " << flow << endl;
}

int solve(int u, uint64_t opened, int time_left, int flow)
{
    if (time_left <= 1) // becuse open takes 1min
        return flow;

    auto& mem = memo[opened][u][time_left];
    if (mem > 0) return mem;

    if (F[u] > 0 and (opened & (1<<u)) == 0) {
        opened |= (1<<u);
        --time_left;
        flow += F[u]*time_left;
    }

    for (auto v : adj[u]) {
        auto s = solve(v, opened, time_left-1, flow);
        if (F[v] > 0) {
            opened &= !(1<<v);
        }
        flow = max(flow, s);
    }

    mem = flow;
    return flow;
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
