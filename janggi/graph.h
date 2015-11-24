#ifndef _H_GRAPH
#define _H_GRAPH

#include "defines.h"

class Node;

class Graph
{
public:
  Graph(int stage[kStageHeight][kStageWidth], Turn turn, int maxDepth);
  ~Graph();
  Action MiniMax();

private:
  Graph();  

  Node* root_;
  int maxDepth_;  
};

#endif