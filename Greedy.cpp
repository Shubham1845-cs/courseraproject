#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>
#include <algorithm>

using namespace std;

struct Node {
    char name;
    int priority;
    Node(char n, int p) : name(n), priority(p) {}
    bool operator>(const Node& other) const { return priority > other.priority; }
};

vector<char> greedyBestFirstSearch(unordered_map<char, unordered_map<char, int>> graph, unordered_map<char, int> heuristic, char start, char goal) {
    priority_queue<Node, vector<Node>, greater<Node>> pq;
    unordered_map<char, char> cameFrom;
    pq.push(Node(start, heuristic[start]));
    cameFrom[start] = 0;

    while (!pq.empty()) {
        char current = pq.top().name;
        pq.pop();

        if (current == goal) break;

        for (auto& next : graph[current]) {
            if (!cameFrom.count(next.first)) {
                pq.push(Node(next.first, heuristic[next.first]));
                cameFrom[next.first] = current;
            }
        }
    }

    vector<char> path;
    for (char cur = goal; cur != 0; cur = cameFrom[cur]) path.push_back(cur);
    reverse(path.begin(), path.end());
    return path;
}

int main() {
    unordered_map<char, unordered_map<char, int>> graph = {
        {'A', {{'B', 1}, {'C', 4}}},
        {'B', {{'A', 1}, {'C', 2}, {'D', 5}}},
        {'C', {{'A', 4}, {'B', 2}, {'D', 1}}},
        {'D', {{'B', 5}, {'C', 1}}}
    };

    unordered_map<char, int> heuristic = {{'A', 7}, {'B', 6}, {'C', 2}, {'D', 0}};
    char start = 'A';
    char goal = 'D';

    vector<char> path = greedyBestFirstSearch(graph, heuristic, start, goal);

    for (char c : path) cout << c << " ";
    return 0;
}
