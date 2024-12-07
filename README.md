# PP_final

- [參考資料](https://github.com/ibmibmibm/a-puzzle-a-day/tree/main)

- run the code
```
cd parallel
g++ -std=c++20 -Wall -O3 -fopenmp -Iinclude -o Puzzle_solver .\one_level.cpp
g++ -std=c++20 -Wall -O3 -fopenmp -Iinclude -o Puzzle_solver .\two_level.cpp
./Puzzle_solver
```
- 小弟用windows，makefile裡的find用不了...