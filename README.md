# An implementation of Sudoku solver in C++

## How it works
* The sudoku grid should be placed in a text file where the empty cells are filled with zero. Have a look at the `test` directory for example.
* You pass the name of this file to `backtracking_solver`.

## Build system
To build you need cmake. Create a directory where the build files will be placed. Similar to the famous
```bash
make build && cd build && cmake .. && make
```
