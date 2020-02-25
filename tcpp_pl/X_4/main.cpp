#include "general.h"

using namespace std;

// Do not define objects in the header files, only declare them.
// Otherwise, linker error of duplicate symbol when including the header in different files.
int main() {
    Shape* face {new Smiley({1, 1}, 1)};
    vector<Shape*> faces = {new Smiley({1, 1}, 1)};
    return 0;
}
