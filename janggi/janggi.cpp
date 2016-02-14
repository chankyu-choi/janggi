#include <cmath>
#include <stack>
#include <iostream>
#include <algorithm>
#include <cassert>

#include "janggi.h"
#include "defines.h"
#include "board.h"
#include "action.h"
#include "node.h"

const Action Janggi::CalculateNextAction(Turn turn)
{
    //mini-max algorithm
    //Node s = Minmax(curNode, MINMAX_DEPTH, turn); // Minmax returns one of her children.
    
    //alpha-beta prunning
    //Node s = AlphaBeta(curNode, MINMAX_DEPTH, INT_MIN, INT_MAX, turn);
    
    //MCTS algorithm
    Node s = MCTS(turn);
    
    return s.GetAction();
}

void Janggi::Print() {
  rootNode.Print();
}

Node Janggi::Minmax(Node node, int depth, Turn turn) {
    if (depth==0 || //terminal node
#if WIN32        
      abs(node.GetValue()) >= (INT_MAX / 2) // win or lose
      ) {
#else
      fabs(node.GetValue()) >= (INT_MAX / 2) // win or lose
      ) {
#endif
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

Node Janggi::AlphaBeta(Node node, int depth, int alpha, int beta, Turn turn) {
    if (depth==0 || //terminal node
#if WIN32
      abs(node.GetValue()) >= (INT_MAX / 2) // win or lose
      ) {
#else
        fabs(node.GetValue()) >= (INT_MAX/2) // win or lose
        ) {
#endif
        node.SetLeafValue(node.GetValue());
        return node; //only one child. herself.
    }
    
    vector<Node> children = node.GetChildren(turn);
    
    int best_value;
    Node best_node;
    if (turn == TURN_CHO) { //maximizing player
        best_value = INT_MIN;
        best_node.SetLeafValue(best_value);
        for (Node n : children) {
            int v = AlphaBeta(n, depth-1, alpha, beta, TURN_HAN).GetLeafValue();
            if ( beta <= alpha ) break; // beta cut-off
            
            alpha = max(alpha, v);
            if(v > best_value) {
                best_value = v;
                n.SetLeafValue(v);
                best_node = n;
            }
        }
    } else { //TRUN_HAN . minizing player
        best_value = INT_MAX;
        best_node.SetLeafValue(best_value);
        for (Node n : children) {
            int v = AlphaBeta(n, depth-1, alpha, beta, TURN_CHO).GetLeafValue();
            if ( beta <= alpha ) break; // alpha cut-off

            beta = min(beta, v);
            if (v < best_value) {
                best_value = v;
                n.SetLeafValue(v);
                best_node = n;
            }
        }
    }
    
    //debug
    
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
    
    return best_node;
}

Node Janggi::MCTS(Turn turn)
{
  rootNode.Init();
  cout << endl << endl;
  for (int i = 0; i < MCTS_ITERATION; i++) {
    Turn currTurn = turn;
    std::stack<Node*> visited;
    Node* pCur = &rootNode;

    std::stack<double> rewards;

    int selected = 0;
    double curReward = 0.0f;

    // Selection
    Node* first = NULL;
    while (!pCur->isLeaf) {
      selected = pCur->Selection(currTurn);
      pCur = pCur->GetChild(selected);
      if (first == NULL) {
        first = pCur;
      }
      visited.push(pCur);
      curReward = pCur->GetValue();      
      //curReward = pCur->GetScore();
      rewards.push(curReward);
      currTurn = (currTurn == TURN_CHO ? TURN_HAN : TURN_CHO);
    }
#if DEBUG_MCTS
    if (first) {
      cout << "init : (" << first->GetAction().prev.x << "," <<
        first->GetAction().prev.y << ") => (" <<
        first->GetAction().next.x << "," <<
        first->GetAction().next.y << ")" << endl;
    }
#endif
    // Expand
    pCur->Expand(currTurn);
    selected = pCur->Selection(currTurn);
    pCur = pCur->GetChild(selected);
    
    // Simulation
    double value = Simulation(*pCur, currTurn == TURN_CHO ? TURN_HAN : TURN_CHO);
    pCur->totalScore = value;

    // Back Propagation
    while (!visited.empty())
    {
      pCur = visited.top();
      if (currTurn == TURN_CHO)
        pCur->totalScore = min(rewards.top(), value);
      else
        pCur->totalScore = max(rewards.top(), value);

      visited.pop();
      rewards.pop();
      currTurn = (currTurn == TURN_CHO ? TURN_HAN : TURN_CHO);
    }
  }
  int bestNode = 0;
  double bestValue;
  if (turn == TURN_CHO) {
    bestValue = -std::numeric_limits<double>::max();
    for (int i = 0; i < rootNode.children.size(); i++) {
      double value = rootNode.children[i].GetScore();
      if (value > bestValue) {
        bestValue = value;
        bestNode = i;
      }

#if DEBUG_MCTS
      double deb_score = rootNode.children[i].GetScore();
      if (deb_score > 0 && deb_score < 0.001)
        deb_score = 0.001;
      else if (deb_score < 0 && deb_score > -0.001)
        deb_score = -0.001;
      else if (deb_score == 0)
        deb_score = 0;


      std::cout << "(" << rootNode.children[i].GetAction().prev.x << ", "
        << rootNode.children[i].GetAction().prev.y << ") => ("
        << rootNode.children[i].GetAction().next.x << ", "
        << rootNode.children[i].GetAction().next.y << ") : "
        << deb_score << endl;
#endif
    }
  }
  else {
    bestValue = std::numeric_limits<double>::max();
    for (int i = 0; i < rootNode.children.size(); i++) {
      double value = rootNode.children[i].GetScore();
      if (value < bestValue) {
        bestValue = value;
        bestNode = i;
      }
#if DEBUG_MCTS
      double deb_score = rootNode.children[i].GetScore();
      if (deb_score > 0 && deb_score < 0.001)
        deb_score = 0.001;
      else if (deb_score < 0 && deb_score > -0.001)
        deb_score = -0.001;
      else if (deb_score == 0)
        deb_score = 0;


      std::cout << "(" << rootNode.children[i].GetAction().prev.x << ", "
        << rootNode.children[i].GetAction().prev.y << ") => ("
        << rootNode.children[i].GetAction().next.x << ", "
        << rootNode.children[i].GetAction().next.y << ") : "
        << deb_score << endl;
#endif
    }
  }
  return rootNode.children[bestNode];
}

double Janggi::Simulation(Node curNode, Turn turn)
{
  Node s = Minmax(curNode, MCTS_SIMULATION_DEPTH, turn);
  curNode.Init();
  return s.GetValue();
}

void Janggi::PerformAction(Action a) {
  rootNode.DoAction(a);
}