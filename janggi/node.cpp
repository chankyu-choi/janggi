//
//  node.cpp
//
//  Created by pilhoon on 1/18/16.
//

#ifndef node_cpp
#define node_cpp

#include <vector>
#include <cassert>
#include <iostream>

#include "node.h"
#include "board.h"

Node::Node(const Node& n){
    board = n.board;
    action = n.action;
    leafValue = n.leafValue;
} // copy ctor

Node::Node(Board b) {
	board = b;
};

int Node::GetValue() {
    return board.GetValue();
}

vector<Node> Node::GetChildren(Turn turn) {
	vector<Node> children;
	vector<Action> acts = board.GetPossibleActions(turn);
	for(Action a: acts) {
        Node n(board);
        n.DoAction(a);
		children.push_back(n);
	}
	return children;
}

void Node::Print() {
    string s = board.ToString(action.prev);
    std::cout << s;
}

void Node::DoAction(Action a) {
    action = a;
    board.DoAction(a);
}

#endif /* node_cpp */

