#ifndef JANGGI_H
#define JANGGI_H

#include "defines.h"
#include "board.h"
#include "node.h"

class Janggi{ // almost utility class.
public:
    const Action CalculateNextAction(Turn turn);
    Node Minmax(Node n, int depth, Turn turn);
    void Print();
    void PerformAction(Action a);
    
private:
    Node curNode;
};

#endif /* JANGGI_H */
