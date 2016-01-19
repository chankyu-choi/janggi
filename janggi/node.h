//
//  node.h
//
//  Created by pilhoon on 1/18/16.
//

#ifndef node_h
#define node_h

#include <vector>
#include "board.h"

class Node{
public:
    Board board = Board();
    Action action = Action(); // from before state, this action makes this board.
    int leafValue;
    
    Node(){};
    Node(const Node& n); // copy ctor
    Node(Board b);
    int GetValue();
    Action GetAction() { return action; };
    void SetAction(Action a) { action = a; };
    vector<Node> GetChildren(Turn turn);
    void Print();
    void DoAction(Action a);
    int GetLeafValue() { return leafValue; };
    void SetLeafValue(int v) { leafValue = v; };
};

#endif /* node_h */

