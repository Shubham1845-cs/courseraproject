#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>
#include <algorithm>

using namespace std;

struct Node {
    char name;
    int cost;
    Node(char n, int c) : name(n), cost(c) {}
    bool operator>(const Node& other) const { return cost > other.cost; }
};

vector<char> informedSearch(unordered_map<char, unordered_map<char, int>> graph, unordered_map<char, int> heuristic, char start, char goal) {
    priority_queue<Node, vector<Node>, greater<Node>> pq;
    unordered_map<char, char> cameFrom;
    unordered_map<char, int> costSoFar;

    pq.push(Node(start, 0));
    cameFrom[start] = 0;
    costSoFar[start] = 0;

    while (!pq.empty()) {
        char current = pq.top().name;
        pq.pop(); 

        if (current == goal) break;

        for (auto& next : graph[current]) {
            int newCost = costSoFar[current] + next.second;
            if (!costSoFar.count(next.first) || newCost < costSoFar[next.first]) {
                costSoFar[next.first] = newCost;
                int priority = newCost + heuristic[next.first];
                pq.push(Node(next.first, priority));
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

    vector<char> path = informedSearch(graph, heuristic, start, goal);

    for (char c : path) cout << c << " ";
    return 0;
}

