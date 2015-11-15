#ifndef H_JANGGI
#define H_JANGGI

#include <iostream>
#include <vector>
using namespace std;

#define DEBUG_MODE 0

enum UnitID {
  HG, HC, HM, HS, HP, Hs, HJ,
  CG, CC, CM, CS, CP, Cs, CJ,
  IDSize,
};

struct Pos{
  Pos() { }
  Pos(int x, int y) { this->x = x; this->y=y; }
  float Distance(int from_x, int from_y);
  int x, y;
};

enum StageID {
  MSSMSMSM,
};

const int     kStageWidth = 9;
const int     kStageHeight = 10;

class Janggi{
public:
  Janggi();

public:
  void          SetStage(StageID stage_id = MSSMSMSM);
  bool          CheckValidPos(Pos pos);
  const char*   GetUnitID(Pos pos);
  void          Show();  
  bool          Action(Pos current, Pos next);
  void          MovableCanditates(Pos current, vector<Pos>& candidates);
  void          MoveGung(Pos current, vector<Pos>& candidates);
  void          MoveCha(Pos current, vector<Pos>& candidates);
  void          MovePo(Pos current, vector<Pos>& candidates);
  void          MoveMa(Pos current, vector<Pos>& candidates);
  void          MoveSang(Pos current, vector<Pos>& candidates);
  void          MoveJol(Pos current, vector<Pos>& candidates);

private: 
  int           stage_[kStageHeight][kStageWidth];    
  bool          standard_position_;
};

#endif
