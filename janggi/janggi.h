#ifndef JANGGI_H
#define JANGGI_H

#include "defines.h"
#include "board.h"
#include "node.h"

#define DEBUG_MCTS 0

class Janggi{ // almost utility class.
public:
    const Action CalculateNextAction(Turn turn);
    Node Minmax(Node n, int depth, Turn turn);
    Node AlphaBeta(Node node, int depth, int alpha, int beta, Turn turn);    
    Node MCTS(Turn turn);
    double Simulation(Node n, Turn turn);
    void Print();
    void PerformAction(Action a);
    
private:
    Node rootNode;
};

#endif /* JANGGI_H */
