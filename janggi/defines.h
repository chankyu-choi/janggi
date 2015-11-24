#ifndef H_DEFINES
#define H_DEFINES

using namespace std;

const int     kStageWidth = 9;
const int     kStageHeight = 10;

enum UnitID {
  HG, HC, HM, HS, HP, Hs, HJ,
  CG, CC, CM, CS, CP, Cs, CJ,
  IDSize,
};

enum Turn {
  TURN_CHO,
  TURN_HAN
};

const int POINT[IDSize/2] = {
  99999, 13, 5, 3, 7, 3, 2
};

struct Pos{
  Pos() { }
  Pos(int x, int y) { this->x = x; this->y=y; }
  float Distance(int from_x, int from_y);
  int x, y;
};

struct Action{
  Action() {}
  Action(Pos curr, Pos next) {this->curr=curr; this->next=next;}
  Pos curr;
  Pos next;
};

enum StageID {
  MSSMSMSM,
};

#endif
