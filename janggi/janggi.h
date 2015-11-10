#ifndef H_JANGGI
#define H_JANGGI

#include <iostream>
using namespace std;

enum UnitID {
  HG, HC, HM, HS, HP, Hs, HJ,
  CG, CC, CM, CS, CP, Cs, CJ,
  IDSize,
};

struct Pos{
  Pos(int x, int y) { this->x = x; this->y=y; }
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

private:
  
  int           stage_[kStageHeight][kStageWidth];    
};

#endif