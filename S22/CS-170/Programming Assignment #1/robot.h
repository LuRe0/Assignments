#ifndef CS170_ROBOT
#define CS170_ROBOT
#include "grid.h"

namespace CS170 {
  namespace Robot {
    typedef struct _Robot *Instance;
    enum Orientation { NORTH,     EAST,     SOUTH,     WEST,  UNDEF };
                     //    0        1         2          3
                     //    so turn left  (orientation+3)%4
                     //       turn right (orientation+1)%4
    Instance Create(int _x, int _y, Orientation orientation, Grid::Instance _grid);
    void Destroy(Instance robot);
    void Move(Instance robot, char cmd);
    bool QueryPosition(Instance robot, int* x, int* y, Orientation *o);
  }
}
#endif
