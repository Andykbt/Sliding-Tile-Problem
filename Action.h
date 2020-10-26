//
//  Action.h
//  Sliding Tile Puzzle Problem
//
//  Created by Andy Truong on 20/8/20.
//  Copyright © 2020 Andy Truong. All rights reserved.
//

#ifndef Action_h
#define Action_h
struct Action {
    int src;
    int dest;
    
    //print action
    void printAction() {cout << "Moving " << src << " to " << dest << endl;}
};

#endif /* Action_h */
