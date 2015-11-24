#ifndef H_JANGGI
#define H_JANGGI

#include <iostream>
#include <vector>

#include "defines.h"

#define DEBUG_MODE 0

class Node;

class Janggi{
public:
  Janggi();
  void          SetStage(StageID stage_id = MSSMSMSM);
  bool          CheckValidPos(Pos pos);
  const char*   GetUnitID(Pos pos);
  void          Show(Pos prev);  
  bool          PerformAction(Action action);
  static void   MovableCanditates(int stage[kStageHeight][kStageWidth], Pos current, vector<Pos>& candidates);
  static void   MoveGung(int stage[kStageHeight][kStageWidth], Pos current, vector<Pos>& candidates);
  static void   MoveCha(int stage[kStageHeight][kStageWidth], Pos current, vector<Pos>& candidates);
  static void   MovePo(int stage[kStageHeight][kStageWidth], Pos current, vector<Pos>& candidates);
  static void   MoveMa(int stage[kStageHeight][kStageWidth], Pos current, vector<Pos>& candidates);
  static void   MoveSang(int stage[kStageHeight][kStageWidth], Pos current, vector<Pos>& candidates);
  static void   MoveJol(int stage[kStageHeight][kStageWidth], Pos current, vector<Pos>& candidates);
  static int    Evaluate(int stage[kStageHeight][kStageWidth]);
  Action        CalculateNextAction(Turn turn);
  static void   MakeNextStage(Action action, int stage[kStageHeight][kStageWidth]);
  
private: 
  int           stage_[kStageHeight][kStageWidth];      
  //bool          standard_position_; //prototyping 용으로는 굳이 이것까지 고려할 필요는 없을 것 같고, code짜는데 불편해서 일단 주석처리
};

#endif
