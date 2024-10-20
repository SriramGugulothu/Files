#include <iostream>
#include <queue>
#include <vector>

using namespace std;

// Struct to represent the connections of each pipe
struct Node {
    bool left, right, up, down;
};

// Struct to represent a point on the grid
struct Point {
    int x, y;
};

int n, m, sX, sY, len;
vector<vector<int>> arr;  // Grid to represent the pipe type
vector<vector<int>> vis, dis;  // Visited array and distance array

int result;
vector<vector<Node>> pipes;  // Grid to represent the pipe connections
queue<Point> q;  // Queue for BFS traversal

// Function to check if the given cell (i, j) is within the grid boundaries
bool isValid(int i, int j) {
    return (i >= 0 && i < n && j >= 0 && j < m);
}

// Function to perform BFS traversal
void bfs() {
    // Initialize visited and distance arrays
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            vis[i][j] = 0;
            dis[i][j] = 0;
        }
    }

    // Set starting point as visited and initialize distance
    dis[sX][sY] = 1;
    vis[sX][sY] = 1;

    // If the starting cell has no pipe, the result is 0
    if (arr[sX][sY] == 0) {
        result = 0;
        return;
    }

    // Start BFS from the starting point
    q.push({sX, sY});

    while (!q.empty()) {
        // Get the front element of the queue
        Point current = q.front();
        q.pop();
        int p = current.x;
        int qPos = current.y;

        // Only proceed if the current distance is within the allowed length
        if (1 + dis[p][qPos] <= len) {

            // Move Up
            if (isValid(p - 1, qPos) && vis[p - 1][qPos] == 0 && pipes[p - 1][qPos].down && pipes[p][qPos].up) {
                vis[p - 1][qPos] = 1;
                dis[p - 1][qPos] = 1 + dis[p][qPos];
                result++;
                q.push({p - 1, qPos});
            }

            // Move Down
            if (isValid(p + 1, qPos) && vis[p + 1][qPos] == 0 && pipes[p + 1][qPos].up && pipes[p][qPos].down) {
                vis[p + 1][qPos] = 1;
                dis[p + 1][qPos] = 1 + dis[p][qPos];
                result++;
                q.push({p + 1, qPos});
            }

            // Move Left
            if (isValid(p, qPos - 1) && vis[p][qPos - 1] == 0 && pipes[p][qPos - 1].right && pipes[p][qPos].left) {
                vis[p][qPos - 1] = 1;
                dis[p][qPos - 1] = 1 + dis[p][qPos];
                result++;
                q.push({p, qPos - 1});
            }

            // Move Right
            if (isValid(p, qPos + 1) && vis[p][qPos + 1] == 0 && pipes[p][qPos + 1].left && pipes[p][qPos].right) {
                vis[p][qPos + 1] = 1;
                dis[p][qPos + 1] = 1 + dis[p][qPos];
                result++;
                q.push({p, qPos + 1});
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while (t--) {
        result = 1;
        cin >> n >> m >> sX >> sY >> len;

        // Initialize grids
        arr.assign(n, vector<int>(m));
        vis.assign(n, vector<int>(m));
        dis.assign(n, vector<int>(m));
        pipes.assign(n, vector<Node>(m));

        // Read the grid and initialize pipe connections based on pipe type
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                cin >> arr[i][j];

                // Set pipe connections based on the type of pipe
                if (arr[i][j] == 1) {
                    pipes[i][j].left = true;
                    pipes[i][j].right = true;
                    pipes[i][j].up = true;
                    pipes[i][j].down = true;
                } else if (arr[i][j] == 2) {
                    pipes[i][j].left = false;
                    pipes[i][j].right = false;
                    pipes[i][j].up = true;
                    pipes[i][j].down = true;
                } else if (arr[i][j] == 3) {
                    pipes[i][j].left = true;
                    pipes[i][j].right = true;
                    pipes[i][j].up = false;
                    pipes[i][j].down = false;
                } else if (arr[i][j] == 4) {
                    pipes[i][j].left = false;
                    pipes[i][j].right = true;
                    pipes[i][j].up = true;
                    pipes[i][j].down = false;
                } else if (arr[i][j] == 5) {
                    pipes[i][j].left = false;
                    pipes[i][j].right = true;
                    pipes[i][j].up = false;
                    pipes[i][j].down = true;
                } else if (arr[i][j] == 6) {
                    pipes[i][j].left = true;
                    pipes[i][j].right = false;
                    pipes[i][j].up = false;
                    pipes[i][j].down = true;
                } else if (arr[i][j] == 7) {
                    pipes[i][j].left = true;
                    pipes[i][j].right = false;
                    pipes[i][j].up = true;
                    pipes[i][j].down = false;
                } else {
                    pipes[i][j].left = false;
                    pipes[i][j].right = false;
                    pipes[i][j].up = false;
                    pipes[i][j].down = false;
                }
            }
        }

        // Perform BFS to find reachable cells
        bfs();
        cout << result << "\n";
    }
    return 0;
}

