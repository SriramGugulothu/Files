#include <iostream>
#include <queue>
#include <vector>

using namespace std;

// Struct to represent a point in the grid
struct Point {
    int x, y;
};

int n, sX, sY, tX, tY;
vector<vector<int>> mat, dis, vis;  // Grid for matrix, distances, and visited status

queue<Point> q;  // Queue for BFS traversal

// Directions for moving in four possible ways: up, down, left, right
vector<int> dirX = {1, 0, -1, 0};
vector<int> dirY = {0, 1, 0, -1};

// Function to check if the given cell (i, j) is within grid boundaries
bool isValid(int i, int j) {
    return (i >= 0 && i < n && j >= 0 && j < n);
}

// Function to perform BFS traversal to calculate frog jumps
void calculateFrogJump() {
    q.push({sX, sY});  // Start BFS from the source point

    vis[sX][sY] = 1;
    dis[sX][sY] = 0;

    while (!q.empty()) {
        Point current = q.front();
        q.pop();
        int p = current.x;
        int qPos = current.y;

        // Explore all four possible directions
        for (int i = 0; i < 4; i++) {
            int newX = p + dirX[i];
            int newY = qPos + dirY[i];

            // Check if the new position is valid, accessible, and not visited
            if (isValid(newX, newY) && mat[newX][newY] == 1 && vis[newX][newY] == 0) {
                // Determine the cost of the move
                if (i == 0 || i == 2) {  // Horizontal move (up or down)
                    dis[newX][newY] = dis[p][qPos];
                } else if (i == 1 || i == 3) {  // Vertical move (left or right)
                    dis[newX][newY] = 1 + dis[p][qPos];
                }

                // Mark the new position as visited
                vis[newX][newY] = 1;

                // Add the new position to the queue
                q.push({newX, newY});
            }
        }
    }
    // Output the distance to the target point
    cout << dis[tX][tY] << endl;
}

int main() {
    cin >> n;

    // Initialize the grid, visited, and distance vectors
    mat.assign(n, vector<int>(n));
    vis.assign(n, vector<int>(n, 0));
    dis.assign(n, vector<int>(n, 0));

    // Read the matrix values
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> mat[i][j];
        }
    }

    // Read the source and target coordinates
    cin >> sX >> sY >> tX >> tY;

    // Perform BFS to calculate frog jumps
    calculateFrogJump();
    
    return 0;
}

