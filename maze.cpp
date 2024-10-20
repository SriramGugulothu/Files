#include <iostream>
#include <vector>
#include <climits>
using namespace std;

// Directions: Down, Right, Up, Left
const int dirX[] = {1, 0, -1, 0};
const int dirY[] = {0, 1, 0, -1};

// Maximum maze size
const int MAX_N = 10;

// Global variables to track the best path and maximum jewels
int best_jewels;
vector<vector<int>> best_path;

// Function to check if the next move is within bounds and not a wall
bool isValid(int x, int y, int N, const vector<vector<int>> &maze, const vector<vector<int>> &visited) {
    return (x >= 0 && x < N && y >= 0 && y < N && maze[x][y] != 1 && !visited[x][y]);
}

// Function to print the maze with the path
void printMaze(const vector<vector<int>> &maze, int N) {
    for(int i = 0; i < N; ++i){
        for(int j = 0; j < N; ++j){
            cout << maze[i][j] << " ";
        }
        cout << endl;
    }
}

// DFS function to explore all possible paths
void dfs(int x, int y, int N, const vector<vector<int>> &maze, vector<vector<int>> &visited, 
         vector<vector<int>> &current_path, int current_jewels) {
    
    // If current cell has a jewel, collect it
    if(maze[x][y] == 2){
        current_jewels++;
    }

    // Mark the current cell as visited and part of the current path
    visited[x][y] = 1;
    current_path[x][y] = 3;

    // If exit is reached, update the best result if necessary
    if(x == N-1 && y == N-1){
        if(current_jewels > best_jewels){
            best_jewels = current_jewels;
            best_path = current_path;
        }
    }
    else{
        // Explore all four directions
        for(int i = 0; i < 4; ++i){
            int newX = x + dirX[i];
            int newY = y + dirY[i];
            if(isValid(newX, newY, N, maze, visited)){
                dfs(newX, newY, N, maze, visited, current_path, current_jewels);
            }
        }
    }

    // Backtrack: Unmark the current cell
    visited[x][y] = 0;
    current_path[x][y] = maze[x][y];
}

int main(){
    int T;
    cin >> T;
    while(T--){
        int N;
        cin >> N;
        vector<vector<int>> maze(N, vector<int>(N, 0));
        for(int i = 0; i < N; ++i){
            for(int j = 0; j < N; ++j){
                cin >> maze[i][j];
            }
        }

        // Initialize visited and current path matrices
        vector<vector<int>> visited(N, vector<int>(N, 0));
        vector<vector<int>> current_path(N, vector<int>(N, 0));
        best_jewels = INT_MIN;
        best_path = maze; // Initialize best_path with the original maze

        // Start DFS from the entrance (0,0)
        dfs(0, 0, N, maze, visited, current_path, 0);

        // Handle case where entrance has a jewel
        if(maze[0][0] == 2 && best_jewels < 1){
            best_jewels = 1;
            best_path = current_path;
        }

        // Print the best path
        printMaze(best_path, N);

        // Print the number of jewels collected
        cout << best_jewels << endl;

        // Print an empty line to separate test cases
        cout << endl;
    }
    return 0;
}

