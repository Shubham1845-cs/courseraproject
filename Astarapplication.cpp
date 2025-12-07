#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

struct Node {
    int x, y, g, h;
};

bool operator<(const Node &a, const Node &b) {
    return (a.g + a.h) > (b.g + b.h);
}

int h(int x, int y, int gx, int gy) {
    return abs(x - gx) + abs(y - gy);
}

bool valid(int x, int y, vector<vector<int>>& maze) {
    return x >= 0 && y >= 0 &&
           x < maze.size() && y < maze[0].size() &&
           maze[x][y] == 0;
}

int main() {
    vector<vector<int>> maze = {
        {0,0,0,1,0},
        {1,1,0,1,0},
        {0,0,0,0,0},
        {0,1,1,1,0},
        {0,0,0,0,0} 
    };

    int sx = 0, sy = 0;        // Start
    int gx = 4, gy = 4;        // Goal

    priority_queue<Node> pq;
    pq.push({sx, sy, 0, h(sx, sy, gx, gy)});

    vector<vector<int>> g(5, vector<int>(5, 9999));
    g[sx][sy] = 0;

    vector<vector<pair<int,int>>> parent(5, vector<pair<int,int>>(5, {-1,-1}));

    int dx[4] = {1,-1,0,0};
    int dy[4] = {0,0,1,-1};

    while (!pq.empty()) {
        Node cur = pq.top(); pq.pop();

        if (cur.x == gx && cur.y == gy) break;

        for (int i = 0; i < 4; i++) {
            int nx = cur.x + dx[i];
            int ny = cur.y + dy[i];

            if (valid(nx, ny, maze)) {
                int newG = cur.g + 1;

                if (newG < g[nx][ny]) {
                    g[nx][ny] = newG;
                    parent[nx][ny] = {cur.x, cur.y};
                    pq.push({nx, ny, newG, h(nx, ny, gx, gy)});
                }
            }
        }
    }

    // Reconstruct the path
    vector<pair<int,int>> path;
    int x = gx, y = gy;

    while (!(x == sx && y == sy)) {
        path.push_back({x, y});
        auto p = parent[x][y];
        x = p.first;
        y = p.second;
    } 
    path.push_back({sx, sy});
    reverse(path.begin(), path.end());

    // Print path
    cout << "A* Path: ";
    for (auto &step : path)
        cout << "(" << step.first << "," << step.second << ") ";
    cout << endl;

    return 0;
}
