#include <cmath>
#include <algorithm>

#include "janggi.h"
#include "defines.h"
#include "board.h"
#include "action.h"
#include "node.h"

const Action Janggi::CalculateNextAction(Turn turn)
{
    //mini-max algorithm
    Node s = Minmax(curNode, MINMAX_DEPTH, turn); // Minmax returns one of her children.
    return s.GetAction();
}

void Janggi::Print() {
    curNode.Print();
}

Node Janggi::Minmax(Node node, int depth, Turn turn) {
    if (depth==0 || //terminal node
        fabs(node.GetValue()) >= (INT_MAX/2) // win or lose
        ) {
        node.SetLeafValue(node.GetValue());
        return node; //only one child. herself.
    }
    
    vector<Node> children = node.GetChildren(turn);
    
    int best_value;
    Node best_node;
    if (turn == TURN_CHO) { //maximizing player
        best_value = INT_MIN;
        for (Node n : children) {
            int v = Minmax(n, depth-1, TURN_HAN).GetLeafValue();
            if(v > best_value) {
                best_value = v;
                n.SetLeafValue(v);
                best_node = n;
            }
        }
    } else { //TRUN_HAN . minizing player
        best_value = INT_MAX;
        for (Node n : children) {
            int v = Minmax(n, depth-1, TURN_CHO).GetLeafValue();
            if (v < best_value) {
                best_value = v;
                n.SetLeafValue(v);
                best_node = n;
            }
        }
    }
    
    //debug
    /*
    if ( depth == MINMAX_DEPTH) {
        int i=0;
        for (Node n: children) {
            Board b= n.board;
            printf("%d) %d,%d -> %d,%d\n", i++, n.GetAction().prev.x, n.GetAction().prev.y, n.GetAction().next.x, n.GetAction().next.y);
        }
        printf("best : %d,%d -> %d,%d. best_score = %d\n",
               best_node.GetAction().prev.x,
               best_node.GetAction().prev.y,
               best_node.GetAction().next.x,
               best_node.GetAction().next.y,
               best_value);
    }
    */
    return best_node;
}

void Janggi::PerformAction(Action a) {
    curNode.DoAction(a);
}

