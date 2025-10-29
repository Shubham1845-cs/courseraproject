#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>

using namespace std;
 
struct Cell {
    bool visited;
    bool walls[4]; 
    bool isPath;   
    Cell() : visited(false), walls{true, true, true, true}, isPath(false) {}
};

const int ROWS = 10;
const int COLS = 10;
vector<vector<Cell>> maze(ROWS, vector<Cell>(COLS));

int dx[] = {-1, 0, 1, 0}; 
int dy[] = {0, 1, 0, -1};

bool   inBounds(int x, int y) {
    return x >= 0 && x < ROWS && y >= 0 && y < COLS;
}

void removeWall(Cell &a, Cell &b, int dir) {    
    a.walls[dir] = false;
    b.walls[(dir + 2) % 4] = false; 
}

void dfsMaze(int x, int y) {
    maze[x][y].visited = true;
    vector<int> dirs = {0, 1, 2, 3};
    random_shuffle(dirs.begin(), dirs.end());

    for (int dir : dirs) {
        int nx = x + dx[dir], ny = y + dy[dir];
        if (inBounds(nx, ny) && !maze[nx][ny].visited) {
            removeWall(maze[x][y], maze[nx][ny], dir);
            dfsMaze(nx, ny);
        }
    }
}

bool dfsSolve(int x, int y) {
    if (!inBounds(x, y) || maze[x][y].isPath)
        return false;
    maze[x][y].isPath = true;
    if (x == ROWS - 1 && y == COLS - 1)
        return true;

    for (int dir = 0; dir < 4; ++dir) {
        int nx = x + dx[dir], ny = y + dy[dir];
        if (!maze[x][y].walls[dir] && !maze[nx][ny].isPath) {
            if (dfsSolve(nx, ny))
                return true;
        } 
    }
    maze[x][y].isPath = false;
    return false;
}

void printMaze() {
    for (int i = 0; i < COLS; ++i)
        cout << " _";
    cout << '\n';

    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            cout << (maze[i][j].walls[3] ? "|" : " ");
            if (maze[i][j].isPath)
                cout << "*";
            else
                cout << (maze[i][j].walls[2] ? "_" : " ");
        }
        cout << "|\n";
    }
}

int main() {
    srand(time(0));
    dfsMaze(0, 0);
    dfsSolve(0, 0);
    printMaze();

    return 0;
}
