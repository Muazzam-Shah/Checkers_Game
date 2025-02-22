#include <iostream>
#include <cstdlib>
using namespace std;

class Piece {
public:
    int Player; 
    int LocationX;
    int LocationY;  
    bool IsKing;

    // Static board array.
    static Piece board[8][8];

    Piece(int player = 0, int x = 0, int y = 0, bool isKing = false) {
        Player = player;
        LocationX = x;
        LocationY = y;
        IsKing = isKing;
    }
    
    // Display the current board.
    static void DisplayBoard() {
        cout << "   0 1 2 3 4 5 6 7\n\n";
        for (int row = 0; row < 8; row++) {
            cout << row << "  ";
            for (int col = 0; col < 8; col++) {
                if (board[row][col].Player == 1)
                    cout << (board[row][col].IsKing ? "R " : "r ");
                else if (board[row][col].Player == 2)
                    cout << (board[row][col].IsKing ? "W " : "w ");
                else
                    cout << "- ";
            }
            cout << row << "\n";
        }
        cout << "\n   0 1 2 3 4 5 6 7\n";
    }

    // Promote a piece if it has reached the opposite end.
    static void PromoteIfNeeded(int destx, int desty) {
        if (board[destx][desty].Player == 1 && destx == 7)
            board[destx][desty].IsKing = true;
        else if (board[destx][desty].Player == 2 && destx == 0)
            board[destx][desty].IsKing = true;
    }
};

Piece Piece::board[8][8];

// Utility: Check if (x,y) is on the board.
bool inBounds(int x, int y) {
    return (x >= 0 && x < 8 && y >= 0 && y < 8);
}

// Pure validation for a simple (non-jump) move.
bool isValidSimpleMove(int currx, int curry, int destx, int desty) {
    if (!inBounds(currx, curry) || !inBounds(destx, desty))
        return false;
    if (Piece::board[destx][desty].Player != 0)
        return false;
    if (abs(currx - destx) != 1 || abs(curry - desty) != 1)
        return false;
    Piece movingPiece = Piece::board[currx][curry];
    if (movingPiece.Player == 0)
        return false;
    // Non-king pieces can only move forward.
    if (!movingPiece.IsKing) {
        if (movingPiece.Player == 1 && destx <= currx)
            return false;
        if (movingPiece.Player == 2 && destx >= currx)
            return false;
    }
    return true;
}

// Pure validation for a jump move.
bool isValidJumpMove(int currx, int curry, int destx, int desty) {
    if (!inBounds(currx, curry) || !inBounds(destx, desty))
        return false;
    if (Piece::board[destx][desty].Player != 0)
        return false;
    if (abs(currx - destx) != 2 || abs(curry - desty) != 2)
        return false;
    Piece movingPiece = Piece::board[currx][curry];
    if (movingPiece.Player == 0)
        return false;
    // Non-king pieces can only jump forward.
    if (!movingPiece.IsKing) {
        if (movingPiece.Player == 1 && destx <= currx)
            return false;
        if (movingPiece.Player == 2 && destx >= currx)
            return false;
    }
    int midx = (currx + destx) / 2;
    int midy = (curry + desty) / 2;
    Piece middlePiece = Piece::board[midx][midy];
    // Must jump over an opponent's piece.
    if (middlePiece.Player == 0 || middlePiece.Player == movingPiece.Player)
        return false;
    return true;
}

// Execute a simple move (after validation).
void executeSimpleMove(int currx, int curry, int destx, int desty) {
    Piece::board[destx][desty] = Piece::board[currx][curry];
    Piece::board[destx][desty].LocationX = destx;
    Piece::board[destx][desty].LocationY = desty;
    Piece::board[currx][curry] = Piece();
    Piece::PromoteIfNeeded(destx, desty);
}

// Execute a jump move (after validation).
void executeJumpMove(int currx, int curry, int destx, int desty) {
    int midx = (currx + destx) / 2;
    int midy = (curry + desty) / 2;
    // Remove the captured piece.
    Piece::board[midx][midy] = Piece();
    // Move the jumping piece.
    Piece::board[destx][desty] = Piece::board[currx][curry];
    Piece::board[destx][desty].LocationX = destx;
    Piece::board[destx][desty].LocationY = desty;
    Piece::board[currx][curry] = Piece();
    Piece::PromoteIfNeeded(destx, desty);
}

// Check if a piece at (x,y) can perform any jump.
bool canJump(int x, int y) {
    int directions[4][2] = { {2, 2}, {2, -2}, {-2, 2}, {-2, -2} };
    for (int i = 0; i < 4; i++) {
        int newX = x + directions[i][0];
        int newY = y + directions[i][1];
        if (isValidJumpMove(x, y, newX, newY))
            return true;
    }
    return false;
}

// Check if one of the players has won.
int CheckWinner() {
    int countPlayer1 = 0, countPlayer2 = 0;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (Piece::board[i][j].Player == 1)
                countPlayer1++;
            else if (Piece::board[i][j].Player == 2)
                countPlayer2++;
        }
    }
    if (countPlayer1 == 0) {
        cout << "Player 2 wins!" << endl;
        return 2;
    } else if (countPlayer2 == 0) {
        cout << "Player 1 wins!" << endl;
        return 1;
    }
    return 0;
}

int main(){
    // Initialize board with player 1's pieces.
    Piece::board[0][1] = Piece(1, 0, 1, false);
    Piece::board[0][3] = Piece(1, 0, 3, false);
    Piece::board[0][5] = Piece(1, 0, 5, false);
    Piece::board[0][7] = Piece(1, 0, 7, false);
    Piece::board[1][0] = Piece(1, 1, 0, false);
    Piece::board[1][2] = Piece(1, 1, 2, false);
    Piece::board[1][4] = Piece(1, 1, 4, false);
    Piece::board[1][6] = Piece(1, 1, 6, false);
    Piece::board[2][1] = Piece(1, 2, 1, false);
    Piece::board[2][3] = Piece(1, 2, 3, false);
    Piece::board[2][5] = Piece(1, 2, 5, false);
    Piece::board[2][7] = Piece(1, 2, 7, false);

    // Initialize board with player 2's pieces.
    Piece::board[5][0] = Piece(2, 5, 0, false);
    Piece::board[5][2] = Piece(2, 5, 2, false);
    Piece::board[5][4] = Piece(2, 5, 4, false);
    Piece::board[5][6] = Piece(2, 5, 6, false);
    Piece::board[6][1] = Piece(2, 6, 1, false);
    Piece::board[6][3] = Piece(2, 6, 3, false);
    Piece::board[6][5] = Piece(2, 6, 5, false);
    Piece::board[6][7] = Piece(2, 6, 7, false);
    Piece::board[7][0] = Piece(2, 7, 0, false);
    Piece::board[7][2] = Piece(2, 7, 2, false);
    Piece::board[7][4] = Piece(2, 7, 4, false);
    Piece::board[7][6] = Piece(2, 7, 6, false);

    cout << "***CHECKERS GAME***\n";
    cout << "A capital letter represents a king piece.\n";
    cout << "Rows and columns are 0-indexed.\n";

    int currentPlayer = 1;
    bool gameover = false;
    int winner = 0;
    int currx, curry, destx, desty;

    Piece::DisplayBoard();

    while (!gameover) {
        cout << "\nPlayer " << currentPlayer << "'s turn." << endl;
        bool moveMade = false;
        while (!moveMade) {
            cout << "Enter current position (row column): ";
            cin >> currx >> curry;
            if (!inBounds(currx, curry)) {
                cout << "Invalid current position. Try again." << endl;
                continue;
            }
            if (Piece::board[currx][curry].Player != currentPlayer) {
                cout << "No valid piece at that position. Try again." << endl;
                continue;
            }
            cout << "Enter destination position (row column): ";
            cin >> destx >> desty;
            if (!inBounds(destx, desty)) {
                cout << "Invalid destination position. Try again." << endl;
                continue;
            }
            if (isValidSimpleMove(currx, curry, destx, desty)) {
                executeSimpleMove(currx, curry, destx, desty);
                moveMade = true;
            } 
            else if (isValidJumpMove(currx, curry, destx, desty)) {
                executeJumpMove(currx, curry, destx, desty);
                moveMade = true;
                // Check for additional jumps from the new location.
                while (canJump(destx, desty)) {
                    cout << "Additional jump available from (" << destx << ", " << desty << ")." << endl;
                    cout << "Do you want to perform an additional jump? (y/n): ";
                    char choice;
                    cin >> choice;
                    if (choice != 'y' && choice != 'Y')
                        break;
                    bool extraJumpMade = false;
                    while (!extraJumpMade) {
                        cout << "Enter new destination for jump from (" << destx << ", " << desty << "): ";
                        int newDestx, newDesty;
                        cin >> newDestx >> newDesty;
                        if (isValidJumpMove(destx, desty, newDestx, newDesty)) {
                            executeJumpMove(destx, desty, newDestx, newDesty);
                            destx = newDestx;
                            desty = newDesty;
                            extraJumpMade = true;
                        } else {
                            cout << "Invalid jump move. Try again." << endl;
                        }
                    }
                }
            } 
            else {
                cout << "Move is invalid. Try again." << endl;
            }
        }
        Piece::DisplayBoard();
        winner = CheckWinner();
        if (winner != 0) {
            gameover = true;
            cout << "Player " << winner << " has won the game!" << endl;
            break;
        }
        // Switch turns.
        currentPlayer = (currentPlayer == 1) ? 2 : 1;
    }
    return 0;
}
