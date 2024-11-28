#include <iostream>
#include <vector>
using namespace std;
// Function to print the solution (board configuration)
void printSolution(const vector<vector<int>>& board, int N) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cout << (board[i][j] ? "Q " : ". ");
        }
        cout << endl;
    }
}
// Function to check if a queen can be placed on board[row][col]
bool isSafe(const vector<vector<int>>& board, int row, int col, int N) {
    // Check the row on the left side
    for (int i = 0; i < col; ++i)
        if (board[row][i])
            return false;
    // Check upper diagonal on the left side
    for (int i = row, j = col; i >= 0 && j >= 0; --i, --j)
        if (board[i][j])
            return false;
    // Check lower diagonal on the left side
    for (int i = row, j = col; j >= 0 && i < N; ++i, --j)
        if (board[i][j])
            return false;
    return true;
}
// Function to solve N-Queen problem using backtracking
bool solveNQUtil(vector<vector<int>>& board, int col, int N) {
    // Base case: If all queens are placed, return true
    if (col >= N)
        return true;
    // Try placing a queen in all rows one by one for this column
    for (int i = 0; i < N; ++i) {
        if (isSafe(board, i, col, N)) {
            board[i][col] = 1; // Place queen
            // Recursively place queens in the next columns
            if (solveNQUtil(board, col + 1, N))
                return true;
            board[i][col] = 0; // Backtrack: Remove the queen
        }
    }
    // If the queen cannot be placed in any row for this column
    return false;
}
// Function to solve the N-Queen problem
void solveNQ(int N) {
    vector<vector<int>> board(N, vector<int>(N, 0));
    if (solveNQUtil(board, 0, N))
        printSolution(board, N);
    else
        cout << "No solution exists for " << N << "-Queens problem." << endl;
}
int main() {
    int N;
    cout << "Enter the number of queens: ";
    cin >> N;
    solveNQ(N);
    return 0;
}
