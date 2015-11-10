#include <iostream>
#include <string>
using namespace std;   

#include "janggi.h"

bool string2ints(string in, int& cx, int& cy, int& nx, int& ny);

void main()
{
  Janggi Janggi;
  Janggi.Show();

  int cx, cy, nx, ny;
  string inputs;
  do {
    cout << "Act : ";
    getline(cin, inputs);
    
    if (string2ints(inputs, cx, cy, nx, ny) && Janggi.Action(cx, cy, nx, ny))
      Janggi.Show();
    else
      cout << "Can't move" << endl;
  } while (1);
}

bool string2ints(string in, int& cx, int& cy, int& nx, int& ny)
{
  if (in.size() != 4)
    return false;

  cx = in[0]-48;
  cy = in[1]-48;
  nx = in[2]-48;
  ny = in[3]-48;

  return true;
}