#include "Janggi.h"

const char* UnitIDChar[IDSize] = {
  "HG", "HC", "HM", "HS", "HP", "Hs", "HJ",
  "CG", "CC", "CM", "CS", "CP", "Cs", "CJ",
};

float Pos::Distance(int x, int y)
{
  return sqrt(pow(this->x - x, 2) + pow(this->y - y, 2));
}

Janggi::Janggi() {
  for (int y = 0; y < kStageHeight; y++) {
    for (int x = 0; x < kStageWidth; x++) {
      stage_[y][x] = -1;
    }
  }

  SetStage(MSSMSMSM);
}

bool Janggi::CheckValidPos(Pos pos)
{
  if (pos.x < 0 || pos.x >= kStageWidth || pos.y < 0 || pos.y >= kStageHeight)
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

const char* Janggi::GetUnitID(Pos pos)
{
  if (!CheckValidPos(pos))
    return NULL;

  if (stage_[pos.y][pos.x] >= 0)
    return UnitIDChar[stage_[pos.y][pos.x]];
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
      cout << GetUnitID(Pos(x, y));
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
  cout << endl << "====================================" << endl;
}

bool Janggi::Action(Pos current, Pos next)
{
  if (!CheckValidPos(current) || !CheckValidPos(next) || stage_[current.y][current.x] < 0)
    return false;
  
  vector<Pos> candidates;
  MovableCanditates(current, candidates);

#if DEBUG_MODE
  for (int i = 0; i < candidates.size(); i++) {
    cout << candidates[i].x << ", " << candidates[i].y << endl;
  }
#endif

  if (candidates.size() != 0) {
    stage_[next.y][next.x] = stage_[current.y][current.x];
    stage_[current.y][current.x] = -1;
  }
}

void Janggi::MovableCanditates(Pos pos, vector<Pos>& candidates)
{
  candidates.clear();
  
  int curr_id = stage_[pos.y][pos.x];

  if (curr_id < 0) {
    return;
  }
  else if (curr_id == HG || curr_id == CG 
          || curr_id == Hs || curr_id == Cs) {
    int nx, ny;
    for (int dy = -1; dy <= 1; dy++) {
      for (int dx = -1; dx <= 1; dx++) {
        nx = pos.x + dx;
        ny = pos.y + dy;
        if ((pos.x == 3 && (pos.y == 1 || pos.y == 8)) ||
          (pos.x == 4 && (pos.y == 0 || pos.y == 2 || pos.y == 7 || pos.y == 9)) ||
          (pos.x == 5 && (pos.y == 1 || pos.y == 8))) {
          // movable to only up, right, left, down side
          if (pos.Distance(nx, ny) > 1)
            continue;
        }
        if (nx >= 3 && nx <= 5
          && ((ny >= 0 && ny <= 2) || (ny >= 7 && ny <= 9))) {
          if (curr_id <= 6) {
            if (stage_[ny][nx]<0 || stage_[ny][nx]>6) {
              candidates.push_back(Pos(nx, ny));
            }
          }
          else {
            if (stage_[ny][nx]<0 || stage_[ny][nx] <= 6) {
              candidates.push_back(Pos(nx, ny));
            }
          }
        }
      }
    }
  }
  else if (curr_id == HC || curr_id == CC) {

  }
  else if (curr_id == HM || curr_id == CM) {

  }
  else if (curr_id == HS || curr_id == CS) {

  }
  else if (curr_id == HP || curr_id == CP) {

  }  
  else if (curr_id == HJ || curr_id == CJ) {

  }
}