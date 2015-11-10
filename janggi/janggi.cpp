#include "Janggi.h"

const char* UnitIDChar[IDSize] = {
  "HG", "HC", "HM", "HS", "HP", "Hs", "HJ",
  "CG", "CC", "CM", "CS", "CP", "Cs", "CJ",
};

Janggi::Janggi() {
  for (int y = 0; y < kStageHeight; y++) {
    for (int x = 0; x < kStageWidth; x++) {
      stage_[y][x] = -1;
    }
  }

  SetStage(MSSMSMSM);
}

bool Janggi::CheckValidPos(int x, int y)
{
  if (x < 0 || x >= kStageWidth || y < 0 || y >= kStageHeight)
    return false;
  return true;
}

void Janggi::SetStage(StageID stage_id)
{
  switch (stage_id) {
  case MSSMSMSM:
    stage_[0][0] = HC;  stage_[0][1] = HM;  stage_[0][2] = HS;
    stage_[0][3] = Hs;  stage_[0][5] = Hs;  stage_[0][6] = HS;
    stage_[0][7] = HM;  stage_[0][8] = HC;  stage_[2][1] = HP;
    stage_[2][7] = HP;  stage_[3][0] = HJ;  stage_[3][2] = HJ;
    stage_[3][4] = HJ;  stage_[3][6] = HJ;  stage_[3][8] = HJ;
    stage_[1][4] = HG;

    stage_[9][0] = CC;  stage_[9][1] = CS;  stage_[9][2] = CM;
    stage_[9][3] = Cs;  stage_[9][5] = Cs;  stage_[9][6] = CS;
    stage_[9][7] = CM;  stage_[9][8] = CC;  stage_[7][1] = CP;
    stage_[7][7] = CP;  stage_[6][0] = CJ;  stage_[6][2] = CJ;
    stage_[6][4] = CJ;  stage_[6][6] = CJ;  stage_[6][8] = CJ;
    stage_[8][4] = CG;
    break;
  }
}

const char* Janggi::GetUnitID(int x, int y)
{
  if (!CheckValidPos(x, y))
    return NULL;

  if (stage_[y][x] >= 0)
    return UnitIDChar[stage_[y][x]];
  else {
    return "--";
  }
}

void Janggi::Show()
{
  cout << "   ";
  for (int x = 0; x < kStageWidth; x++)
    cout << x << "   ";
  cout << endl;

  for (int y = 0; y < kStageHeight; y++) {
    cout << y << " ";
    for (int x = 0; x < kStageWidth; x++) {
      cout << GetUnitID(x, y);
      if (x != kStageWidth - 1)
        cout << "  ";
    }
    if (y != kStageHeight - 1) {
      cout << endl << "  ";
      for (int x = 0; x < kStageWidth; x++) {
        cout << "    ";
      }
      cout << endl;
    }
  }
  cout << endl;
}

bool Janggi::Action(int cx, int cy, int nx, int ny)
{
  if (!CheckValidPos(cx, cy) || !CheckValidPos(nx, ny) || stage_[cy][cx] < 0)
    return false;
  
  stage_[ny][nx] = stage_[cy][cx];
  stage_[cy][cx] = -1;
}