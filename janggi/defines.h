#ifndef H_DEFINES
#define H_DEFINES

#include <climits>
#include <utility>
#include <string>
#include "pos.h"

using namespace std;

#define MINMAX_DEPTH 6

const int     kStageWidth = 9;
const int     kStageHeight = 10;

enum UnitID {
  HG, HC, HM, HS, HP, Hs, HJ,
  CG, CC, CM, CS, CP, Cs, CJ,
  IDSize,
};

const string UnitIDChar[IDSize] = {
    "HG", "HC", "HM", "HS", "HP", "Hs", "HJ",
    "CG", "CC", "CM", "CS", "CP", "Cs", "CJ",
};

enum Turn {
  TURN_CHO,
  TURN_HAN
};

const int POINT[IDSize/2] = {
  INT_MAX, 13, 5, 3, 7, 3, 2
};

enum StageID {
  MSSMSMSM,
};

#endif
