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

void calc_total_100000(Node* node, size_t& total)
{
    if (not node || not node->is_dir) return;

    if (node->size < 100'000) {
        total += node->size;
    }
    for (const auto& child : node->children) {
        calc_total_100000(child.get(), total);
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
    size_t total;
    calc_total_100000(root.get(), total);
    cout << endl << "total size: " << total << endl;
}
