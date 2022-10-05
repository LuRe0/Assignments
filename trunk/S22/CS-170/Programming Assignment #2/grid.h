#ifndef CS170_GRID
#define CS170_GRID
namespace CS170 {
  class Grid {
    public:
      Grid(int x, int y);
      ~Grid();
      bool Inside(int x, int y);
      void Mark(int x, int y);
      bool Marked(int x, int y);
    private:
      int x_max, y_max; 
      int* data;
  };
}
#endif
