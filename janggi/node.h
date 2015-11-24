#ifndef H_NODE
#define H_NODE

#include <vector>

#include "defines.h"

class Node {
public:
  Node(int stage[kStageHeight][kStageWidth], int depth, int point, Turn turn, Action lastAction);
  ~Node();
  void MakeChildNodes(int maxDepth);  
  const Action CalculateMiniMaxAction(bool random);
  const Action GetLastAction() { return lastAction_; }

private: 
  Node();
  bool MovableUnitExists(int unitID );
  const int CalculateMiniMaxScore();

  int stage_[kStageHeight][kStageWidth];    
  int depth_;
  int point_; // minimax alg. 에서는 leaf node에서만 이 값이 계산될 필요가 있으나, 일단 모든 node에서 무조건 계산되도록 구현됨.
  int turn_;
  Action lastAction_;
  vector<Node*> childNodes_;
};

#endif