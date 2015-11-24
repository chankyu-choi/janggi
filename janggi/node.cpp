
#include <algorithm>

#include "defines.h"
#include "node.h"
#include "janggi.h"

Node::Node(int stage[kStageHeight][kStageWidth], int depth, int point, Turn turn, Action lastAction)
{
  memcpy(stage_, stage, sizeof(int) * kStageHeight * kStageWidth);
  depth_ = depth;
  point_ = point;
  turn_ = turn;
  lastAction_ = lastAction;
}

Node::~Node()
{
  for (unsigned int i=0 ; i<childNodes_.size() ; i++) {
    delete childNodes_[i];
  }
}

void Node::MakeChildNodes(int maxDepth)
{ 
  if (depth_ >= maxDepth )
    return;

  for (int y=0 ; y<kStageHeight ; y++) {    
    for (int x=0 ; x<kStageWidth ; x++) {      
      if ( MovableUnitExists(stage_[y][x]) ) {
        Pos curr(x,y);
        vector<Pos> candidates;
        Janggi::MovableCanditates(stage_, curr, candidates);                
        for (unsigned int i = 0; i < candidates.size(); i++) {
          int stage[kStageHeight][kStageWidth];
          memcpy(stage, stage_, sizeof(int) * kStageHeight * kStageWidth);
          Janggi::MakeNextStage(Action(curr, candidates[i]), stage);
          Node* node = new Node(stage, 
                                depth_+1, 
                                Janggi::Evaluate(stage), 
                                turn_ == TURN_CHO ? TURN_HAN : TURN_CHO, 
                                Action(curr, candidates[i]));
          childNodes_.push_back(node);
          node->MakeChildNodes(maxDepth);
        }        
      }          
    }
  }  
}

bool Node::MovableUnitExists(int unitID )
{
  if ( unitID < 0 )
    return false;

  if ( ( turn_ == TURN_CHO && unitID > 6 )
     || ( turn_ == TURN_HAN && unitID <= 6 ) )
    return true;

  return false;  
}

const Action Node::CalculateMiniMaxAction(bool random)
{
  int val;  
  vector<int> childScores;
  
  for (unsigned int i=0 ; i<childNodes_.size() ; i++)
    childScores.push_back( childNodes_[i]->CalculateMiniMaxScore() );    

  if (turn_ == TURN_CHO)
    val = *max_element(childScores.begin(), childScores.end());
  else // TURN_HAN
    val = *min_element(childScores.begin(), childScores.end());      
  printf("val=%d\n",val);
  vector<int> candIndices;
  for (unsigned int i=0 ; i<childScores.size() ; i++) {
    if (childScores[i] == val)
      candIndices.push_back(i);
  }

  int index = candIndices[random ? (rand() % candIndices.size()) : 0];  

  return childNodes_[index]->GetLastAction();
}

const int Node::CalculateMiniMaxScore()
{
  if ( childNodes_.empty() )     
    return point_;  

  vector<int> childScores;

  for (unsigned int i=0 ; i<childNodes_.size() ; i++)
    childScores.push_back( childNodes_[i]->CalculateMiniMaxScore() );
    
  if ( turn_ == TURN_CHO )
    return *max_element(childScores.begin(), childScores.end());
  else // TURN_HAN
    return *min_element(childScores.begin(), childScores.end());
}