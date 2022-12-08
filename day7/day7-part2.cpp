#include <bits/stdc++.h>
using namespace std;

struct Node;

struct Node {
    Node* parent{};
    vector<unique_ptr<Node>> children;
    string name;
    size_t size{};
    bool is_dir{false};
};

Node* find_child(Node* parent, const string& name)
{
    if (not parent)  {
        return nullptr;
    }

    auto it = ranges::find_if(parent->children, [&](const auto& ptr) {
            return ptr->name == name;
            });
    if (it == end(parent->children)) {
        return nullptr;
    }

    return it->get();
}

void calc_sizes(Node* node)
{
    if (not node) {
        return;
    }

    size_t size = 0;
    for (const auto& child : node->children) {
        if (child->size == 0 && child->is_dir && child->children.size() > 0) {
            calc_sizes(child.get());
        }
        size += child->size;
    }
    node->size = size;
}

void report_sizes(Node* node, int level)
{
    if (not node || not node->is_dir) return;

    cout << string(level, ' ');
    cout << node->name << ": " << node->size << endl;

    for (const auto& child : node->children) {
        report_sizes(child.get(), level+1);
    }
}

static size_t root_size = 0;

void find_optimum(Node* node, Node*& opt)
{
    static constexpr size_t k_space_all = 70'000'000;
    static constexpr size_t k_space_needed = 30'000'000;

    if (k_space_all - root_size + node->size >= k_space_needed && node->size < opt->size) {
        opt = node;
    }

    for (const auto& child : node->children) {
        if (child->is_dir) {
            find_optimum(child.get(), opt);
        }
    }
}

int main()
{
    auto root = make_unique<Node>();
    root->name = "/";
    root->is_dir = true;

    Node* cur{};

    string line;
    while (getline(cin, line)) {
        istringstream ss(line);

        if (ss.peek() == '$') {
            ss.get();

            string command;
            ss >> command;

            if (command == "cd") {
                string target;
                ss >> target;

                if (target == "/") {
                    cur = root.get();
                }
                else if (target == "..") {
                    cur = cur->parent;
                }
                else {
                    if (auto child = find_child(cur, target); child) {
                        cur = child;
                    }


                }
            }

            else if (command == "ls") {
                continue;
            }

        }
        else if (isdigit(ss.peek())) {
            // size <filename>
            auto child = make_unique<Node>();
            size_t size;
            string name;
            ss >> child->size >> child->name;
            child->parent = cur;
            cur->children.push_back(move(child));
        }
        else {
            string prop;
            ss >> prop;

            if (prop == "dir") {
                string dirname;
                ss >> dirname;
                auto dir = make_unique<Node>();
                dir->name = dirname;
                dir->is_dir = true;
                dir->parent = cur;

                cur->children.push_back(move(dir));
            }
        }
    }

    calc_sizes(root.get());
    report_sizes(root.get(), 0);

    Node* optimum = root.get();
    root_size = root->size;
    find_optimum(root.get(), optimum);
    cout << "smallest dir size to delete: " << optimum->size << endl;
}
