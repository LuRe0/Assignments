#ifndef CS170_ROBOT
#define CS170_ROBOT
#include "grid.h"

namespace CS170 {
  class Robot {
    public:
      enum Orientation {NORTH,EAST,SOUTH,WEST};
      Robot(Grid& _grid,int _x=0, int _y=0, Orientation orientation=SOUTH);
      ~Robot();
      void Move(char cmd);
      int GetX();
      int GetY();
      Orientation GetO();
      bool GetStatus();
    private:
      Grid& grid;
      int x,y;
      Orientation heading;
  };
}
#endif
