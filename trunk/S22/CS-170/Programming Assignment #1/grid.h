#ifndef CS170_GRID
#define CS170_GRID
namespace CS170 {
    namespace Grid {
        typedef struct _Grid *Instance;
        Instance Create(int x, int y);
        void Destroy(Instance grid);
        bool Inside(Instance grid, int x, int y);
        void Mark(Instance grid, int x, int y);
        bool Marked(Instance grid, int x, int y);
    }
}
#endif
