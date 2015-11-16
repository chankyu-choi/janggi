#include <iostream>
#include <string>
using namespace std;   

#include "janggi.h"

bool string2ints(string in, Pos& current, Pos& next);
#define ASCIIBASE 48

int main()
{
  Janggi Janggi;
  Janggi.Show();

  Pos current, next;
  string inputs;
  do {
    cout << "Act : ";
    getline(cin, inputs);
    
    if (string2ints(inputs, current, next) && Janggi.Action(current, next))
      Janggi.Show();
    else
      cout << "Can't move" << endl;
  } while (1);

  return 1;
}

bool string2ints(string in, Pos& current, Pos& next)
{
  if (in.size() != 4)
    return false;

  current.x = in[0] - ASCIIBASE;
  current.y = in[1] - ASCIIBASE;
  next.x = in[2] - ASCIIBASE;
  next.y = in[3] - ASCIIBASE;

  return true;
}