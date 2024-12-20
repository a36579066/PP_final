#pragma once
#include <array>
#include <fstream>
#include <iostream>
#include <span>
#include <vector>
#include <mutex>
#include <thread>


using SolutionBoard = std::array<std::array<uint_fast8_t, 7>, 7>;  // 單個 7x7 棋盤的解
using DailySolutions = std::vector<SolutionBoard>;                 // 一天的所有解
using MonthlySolutions = std::vector<DailySolutions>;              // 每月的所有天解
using YearlySolutions = std::vector<MonthlySolutions>;             // 一整年的所有解

namespace block{
  // Hexomino
  const uint_fast8_t Hexomino[2][4][4] = {
      {
          {1, 1, 1, 0},
          {1, 1, 1, 0},
          {0, 0, 0, 0},
          {0, 0, 0, 0},
      },
      {
          {1, 1, 0, 0},
          {1, 1, 0, 0},
          {1, 1, 0, 0},
          {0, 0, 0, 0},
      },
  };

  // L Pentomino
  const uint_fast8_t L_Pentomino[8][4][4] = {
      {
          {2, 0, 0, 0},
          {2, 2, 2, 2},
          {0, 0, 0, 0},
          {0, 0, 0, 0},
      },
      {
          {2, 2, 0, 0},
          {2, 0, 0, 0},
          {2, 0, 0, 0},
          {2, 0, 0, 0},
      },
      {
          {2, 2, 2, 2},
          {0, 0, 0, 2},
          {0, 0, 0, 0},
          {0, 0, 0, 0},
      },
      {
          {0, 2, 0, 0},
          {0, 2, 0, 0},
          {0, 2, 0, 0},
          {2, 2, 0, 0},
      },
      {
          {2, 2, 2, 2},
          {2, 0, 0, 0},
          {0, 0, 0, 0},
          {0, 0, 0, 0},
      },
      {
          {2, 2, 0, 0},
          {0, 2, 0, 0},
          {0, 2, 0, 0},
          {0, 2, 0, 0},
      },
      {
          {0, 0, 0, 2},
          {2, 2, 2, 2},
          {0, 0, 0, 0},
          {0, 0, 0, 0},
      },
      {
          {2, 0, 0, 0},
          {2, 0, 0, 0},
          {2, 0, 0, 0},
          {2, 2, 0, 0},
      },
  };

  // N Pentomino
  const uint_fast8_t N_Pentomino[8][4][4] = {
      {
          {3, 3, 0, 0},
          {0, 3, 3, 3},
          {0, 0, 0, 0},
          {0, 0, 0, 0},
      },
      {
          {0, 3, 0, 0},
          {3, 3, 0, 0},
          {3, 0, 0, 0},
          {3, 0, 0, 0},
      },
      {
          {3, 3, 3, 0},
          {0, 0, 3, 3},
          {0, 0, 0, 0},
          {0, 0, 0, 0},
      },
      {
          {0, 3, 0, 0},
          {0, 3, 0, 0},
          {3, 3, 0, 0},
          {3, 0, 0, 0},
      },
      {
          {0, 3, 3, 3},
          {3, 3, 0, 0},
          {0, 0, 0, 0},
          {0, 0, 0, 0},
      },
      {
          {3, 0, 0, 0},
          {3, 3, 0, 0},
          {0, 3, 0, 0},
          {0, 3, 0, 0},
      },
      {
          {0, 0, 3, 3},
          {3, 3, 3, 0},
          {0, 0, 0, 0},
          {0, 0, 0, 0},
      },
      {
          {3, 0, 0, 0},
          {3, 0, 0, 0},
          {3, 3, 0, 0},
          {0, 3, 0, 0},
      },
  };

  // P Pentomino
  const uint_fast8_t P_Pentomino[8][4][4] = {
      {
          {4, 4, 4, 0},
          {0, 4, 4, 0},
          {0, 0, 0, 0},
          {0, 0, 0, 0},
      },
      {
          {0, 4, 0, 0},
          {4, 4, 0, 0},
          {4, 4, 0, 0},
          {0, 0, 0, 0},
      },
      {
          {4, 4, 0, 0},
          {4, 4, 4, 0},
          {0, 0, 0, 0},
          {0, 0, 0, 0},
      },
      {
          {4, 4, 0, 0},
          {4, 4, 0, 0},
          {4, 0, 0, 0},
          {0, 0, 0, 0},
      },
      {
          {0, 4, 4, 0},
          {4, 4, 4, 0},
          {0, 0, 0, 0},
          {0, 0, 0, 0},
      },
      {
          {4, 0, 0, 0},
          {4, 4, 0, 0},
          {4, 4, 0, 0},
          {0, 0, 0, 0},
      },
      {
          {4, 4, 4, 0},
          {4, 4, 0, 0},
          {0, 0, 0, 0},
          {0, 0, 0, 0},
      },
      {
          {4, 4, 0, 0},
          {4, 4, 0, 0},
          {0, 4, 0, 0},
          {0, 0, 0, 0},
      },
  };

  // U Pentomino
  const uint_fast8_t U_Pentomino[4][4][4] = {
      {
          {5, 0, 5, 0},
          {5, 5, 5, 0},
          {0, 0, 0, 0},
          {0, 0, 0, 0},
      },
      {
          {5, 5, 0, 0},
          {5, 0, 0, 0},
          {5, 5, 0, 0},
          {0, 0, 0, 0},
      },
      {
          {5, 5, 5, 0},
          {5, 0, 5, 0},
          {0, 0, 0, 0},
          {0, 0, 0, 0},
      },
      {
          {5, 5, 0, 0},
          {0, 5, 0, 0},
          {5, 5, 0, 0},
          {0, 0, 0, 0},
      },
  };

  // V Pentomino
  const uint_fast8_t V_Pentomino[4][4][4] = {
      {
          {6, 0, 0, 0},
          {6, 0, 0, 0},
          {6, 6, 6, 0},
          {0, 0, 0, 0},
      },
      {
          {6, 6, 6, 0},
          {6, 0, 0, 0},
          {6, 0, 0, 0},
          {0, 0, 0, 0},
      },
      {
          {6, 6, 6, 0},
          {0, 0, 6, 0},
          {0, 0, 6, 0},
          {0, 0, 0, 0},
      },
      {
          {0, 0, 6, 0},
          {0, 0, 6, 0},
          {6, 6, 6, 0},
          {0, 0, 0, 0},
      },
  };

  // Y Pentomino
  const uint_fast8_t Y_Pentomino[8][4][4] = {
      {
          {7, 7, 7, 7},
          {0, 7, 0, 0},
          {0, 0, 0, 0},
          {0, 0, 0, 0},
      },
      {
          {0, 7, 0, 0},
          {7, 7, 0, 0},
          {0, 7, 0, 0},
          {0, 7, 0, 0},
      },
      {
          {0, 0, 7, 0},
          {7, 7, 7, 7},
          {0, 0, 0, 0},
          {0, 0, 0, 0},
      },
      {
          {7, 0, 0, 0},
          {7, 0, 0, 0},
          {7, 7, 0, 0},
          {7, 0, 0, 0},
      },
      {
          {7, 7, 7, 7},
          {0, 0, 7, 0},
          {0, 0, 0, 0},
          {0, 0, 0, 0},
      },
      {
          {0, 7, 0, 0},
          {0, 7, 0, 0},
          {7, 7, 0, 0},
          {0, 7, 0, 0},
      },
      {
          {0, 7, 0, 0},
          {7, 7, 7, 7},
          {0, 0, 0, 0},
          {0, 0, 0, 0},
      },
      {
          {7, 0, 0, 0},
          {7, 7, 0, 0},
          {7, 0, 0, 0},
          {7, 0, 0, 0},
      },
  };

  // Z Pentomino
  const uint_fast8_t Z_Pentomino[4][4][4] = {
      {
          {8, 8, 0, 0},
          {0, 8, 0, 0},
          {0, 8, 8, 0},
          {0, 0, 0, 0},
      },
      {
          {0, 0, 8, 0},
          {8, 8, 8, 0},
          {8, 0, 0, 0},
          {0, 0, 0, 0},
      },
      {
          {8, 0, 0, 0},
          {8, 8, 8, 0},
          {0, 0, 8, 0},
          {0, 0, 0, 0},
      },
      {
          {0, 8, 8, 0},
          {0, 8, 0, 0},
          {8, 8, 0, 0},
          {0, 0, 0, 0},
      },
  };

}