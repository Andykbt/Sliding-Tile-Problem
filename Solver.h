//
//  Solver.h
//  Sliding Tile Puzzle Problem
//
//  Created by Andy Truong on 20/8/20.
//  Copyright © 2020 Andy Truong. All rights reserved.
//

#ifndef Solver_h
#define Solver_h
class Solver {
public:
    Solver() {
        priority_queue<Action> pq;
        
        Board b;
        b.randomiseBoard();
        
        cout << "INITIAL BOARD" << endl;
        b.printBoard();
        
        cout << "------------------" << endl;
        cout << "A* SEARCH" << endl;
        cout << "------------------" << endl;
        AStarSearch(b);
    }
    
    bool inClosed(vector<Board> vec, Board b) {
        for (int i = 0; i < vec.size(); i++)
            if (vec[i] == b)
                return true;
        return false;
    }
    
    bool inOpen(priority_queue<Board> pq, Board b) {
        priority_queue<Board> temp = pq;
        while (!temp.empty()) {
            if (temp.top() == b)
                return true;
            temp.pop();
        }
        
        return false;
    }
    
    bool AStarSearch(Board initial) {
        priority_queue<Board> open;
        vector<Board> closed;
        
        open.push(initial);
        
        while(!open.empty()) {
            Board current(open.top());    //copy node with lowest fCost
            closed.push_back(current);
            open.pop();
            
            //current.printBoard();
            
            if (current.isGoal()) {
                cout << "GOAL FOUND AT STEP: " << current.getGCost() << endl;
                current.printBoard();
                return true;
            }
            
            //Generate successors
            vector<Board> successors;
            current.getSuccessors(successors);
            
            for (int i = 0; i < successors.size(); i++) {
                if (inClosed(closed, successors[i]))
                    i++;
                else if (!inOpen(open, successors[i])) {
                    successors[i].setGCost(current.getGCost() + 1);
                    successors[i].getFCost();

                    //cout << "f(n): [" << successors[i].getGCost() << ", " << successors[i].getHCost() << "]" << endl;
                    //successors[i].printBoard();
                    
                    open.push(successors[i]);
                }
            }
        }
        
        return true;
    }
};

#endif /* Solver_h */
