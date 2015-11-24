
#include "graph.h"
#include "node.h"
#include "janggi.h"

Graph::Graph(int stage[kStageHeight][kStageWidth], Turn turn, int maxDepth)
{
  maxDepth_ = maxDepth;
  root_ = new Node(stage, 0, Janggi::Evaluate(stage), turn, Action());    
  root_->MakeChildNodes(maxDepth);
}

Graph::~Graph()
{
  delete root_;
}

Action Graph::MiniMax()
{ 
  return root_->CalculateMiniMaxAction(true);
}