//
//  Board.h
//  Sliding Tile Puzzle Problem
//
//  Created by Andy Truong on 20/8/20.
//  Copyright © 2020 Andy Truong. All rights reserved.
//

#ifndef Board_h
#define Board_h
class Board {
private:
    char board[BOARD_SIZE];
    
    int fCost;
    int gCost = 0;
    int hCost = 0;
public:
    Board() {
        for (int i = 0; i < BOARD_SIZE; i++)
            board[i] = ' ';
    }

    Board(char board[]) {
        for (int i = 0; i < BOARD_SIZE; i++)
            this->board[i] = board[i];
    }
    
    bool operator<(const Board &b) const {return fCost < b.fCost;}
    
    bool operator==(const Board &b) const {
        for (int i = 0; i < BOARD_SIZE; i++) {
            if (board[i] != b.board[i])
                return false;
        }
        return true;
    }
    
    Board nextState(Action a) {
        Board newBoard(*this);
        newBoard.moveTile(a);
        newBoard.setHCost(0);
        //newBoard.setGCost(newBoard.getGCost()+1);
        return newBoard;
    }
    
    int getTile(int i) {return board[i];}
    int getFCost() {return gCost + hCost;}
    int getGCost() {return gCost;}
    int getHCost() {return getHeuristic();}
    
    void setGCost(int gCost) {this->gCost = gCost;}
    void setHCost(int hCost) {this->hCost = hCost;}
    
    void const printBoard() {
        cout << "+";
        for (int i = 0; i < BOARD_SIZE*4 - 1; i++) cout << "-";
        cout << "+" << endl;
        
        for (int i = 0; i < BOARD_SIZE; i++) {cout << "| " << board[i] << " ";}
        cout << "|" << endl;
        
        cout << "+";
        for (int i = 0; i < BOARD_SIZE*4 - 1; i++) cout << "-";
        cout << "+" << endl;
    }
    
    void randomiseBoard() {
        int randomTile;
        for (int i = 0; i < WTILES; i++) {
            randomTile = rand() % BOARD_SIZE;
            if (board[randomTile] != ' ')
                i--;
            else
                board[randomTile] = 'W';
        }
        
        for (int i = 0; i < BTILES; i++) {
            randomTile = rand() % BOARD_SIZE;
            if (board[randomTile] != ' ')
                i--;
            else
                board[randomTile] = 'B';
        }
    }
    
    bool moveTile(int src, int destination) {
        if (canMove(src, destination)) {
            swap(board[src], board[destination]);
            return true;
        }
        return false;
    }
    
    bool moveTile(Action a) {
        if (canMove(a.src, a.dest)) {
            swap(board[a.src], board[a.dest]);
            return true;
        }
        return false;
    }
    
    bool canMove(int src, int destination) {
        int distance = abs(src-destination) - 1;
        if (board[destination] == ' ' && distance < 3)
            return true;
        else
            return false;
    }
    
    bool canMove(Action a) {
        int distance = abs(a.src - a.dest) - 1;
        if (board[a.dest] == ' ' && distance < 4)
            return true;
        else
            return false;
    }
    
    int getHeuristic() {    //heuristic function, returns the number of Wtiles on the left of Btiles
        for (int i = 0; i < BOARD_SIZE; i++) {
            if (board[i] == 'W') {
                for (int j = i; j >= 0; j--)
                    if (board[j] == 'B') {
                        hCost++;
                        break;
                    }
            }
        }
        return hCost;
    }
    
    void possibleMoves(queue<Action> &q) {
        Action a;
        for (int i = 0; i < BOARD_SIZE; i++) {
            for (int j = 0; j < BOARD_SIZE; j++) {
                if (canMove(i, j) && getTile(i) != ' ') {
                    a.src = i;
                    a.dest = j;
                    q.push(a);
                }
            }
        }
    }
    
    bool isGoal() {
        
        int wTiles = 0;
        for (int i = 0; i < BOARD_SIZE; i++) {
            if (board[i] == 'B') {
                //cout << "B tile found at " << i << endl;
                for (int j = i; j >= 0; j--) {
                    if (board[j] == 'W') {
                        wTiles++;
                    }
                }
            }
        }
        
        if (wTiles == 9)
            return true;
        return false;
    }
    
    void getSuccessors(vector<Board> &s) {
        queue<Action> q;
        possibleMoves(q);
        
        //cout << "possible moves: " << q.size() << endl;
        while (!q.empty()) {
            s.push_back(nextState(q.front()));
            q.pop();
        }
    }
};

#endif /* Board_h */
