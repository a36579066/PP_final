#include <array>
#include <fstream>
#include <iostream>
#include <span>

namespace {

uint_fast8_t Board[10][10] = {
    {0, 0, 0, 0, 0, 0, 9, 9, 9, 9}, {0, 0, 0, 0, 0, 0, 9, 9, 9, 9},
    {0, 0, 0, 0, 0, 0, 0, 9, 9, 9}, {0, 0, 0, 0, 0, 0, 0, 9, 9, 9},
    {0, 0, 0, 0, 0, 0, 0, 9, 9, 9}, {0, 0, 0, 0, 0, 0, 0, 9, 9, 9},
    {0, 0, 0, 9, 9, 9, 9, 9, 9, 9}, {9, 9, 9, 9, 9, 9, 9, 9, 9, 9},
    {9, 9, 9, 9, 9, 9, 9, 9, 9, 9}, {9, 9, 9, 9, 9, 9, 9, 9, 9, 9},
};

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

const std::span<const uint_fast8_t[4][4]> Pieces[8] = {
    Hexomino,    L_Pentomino, N_Pentomino, P_Pentomino,
    U_Pentomino, V_Pentomino, Y_Pentomino, Z_Pentomino,
};

bool can_place(const uint_fast8_t shape[4][4], const uint_fast8_t x,
               const uint_fast8_t y) {
  for (uint_fast8_t i = 0; i < 4; ++i) {
    for (uint_fast8_t j = 0; j < 4; ++j) {
      if (shape[j][i] != 0 && Board[y + j][x + i] != 0) {
        return false;
      }
    }
  }
  return true;
}

void place(const uint_fast8_t shape[4][4], const uint_fast8_t x,
           const uint_fast8_t y) {
  for (uint_fast8_t i = 0; i < 4; ++i) {
    for (uint_fast8_t j = 0; j < 4; ++j) {
      if (shape[j][i] != 0) {
        Board[y + j][x + i] = shape[j][i];
      }
    }
  }
}

void unplace(const uint_fast8_t shape[4][4], const uint_fast8_t x,
             const uint_fast8_t y) {
  for (uint_fast8_t i = 0; i < 4; ++i) {
    for (uint_fast8_t j = 0; j < 4; ++j) {
      if (shape[j][i] != 0) {
        Board[y + j][x + i] = 0;
      }
    }
  }
}

bool valid() {
  uint_fast8_t month_count = 0;
  for (uint_fast8_t i = 0; i < 2; ++i) {
    for (uint_fast8_t j = 0; j < 7; ++j) {
      if (Board[i][j] == 0) {
        ++month_count;
        if (month_count > 1) {
          return false;
        }
      }
    }
  }
  if (month_count == 0) {
    return false;
  }
  return true;
}

uint_fast8_t get_month() {
  for (uint_fast8_t i = 0; i < 2; ++i) {
    for (uint_fast8_t j = 0; j < 7; ++j) {
      if (Board[i][j] == 0) {
        return i * 6 + j + 1;
      }
    }
  }
  return 0;
}

uint_fast8_t get_day() {
  for (uint_fast8_t i = 2; i < 7; ++i) {
    for (uint_fast8_t j = 0; j < 7; ++j) {
      if (Board[i][j] == 0) {
        return (i - 2) * 7 + j + 1;
      }
    }
  }
  return 0;
}

void backtrack(uint_fast8_t placed,
               std::span<const std::span<const uint_fast8_t[4][4]>> pieces) {
  using namespace std::literals;
  if (placed == 8) {
    if (!valid()) {
      return;
    }
    const uint16_t month = get_month();
    const uint16_t day = get_day();

    std::ofstream fout(std::to_string(month) + '_' + std::to_string(day) +
                           ".txt"s,
                       std::ios::app);
    for (uint_fast8_t i = 0; i < 7; ++i) {
      for (uint_fast8_t j = 0; j < 7; ++j) {
        fout << static_cast<uint16_t>(Board[i][j]);
      }
      fout << '\n';
    }
    fout << '\n';
    return;
  }
  if (placed + pieces.size() < 8) {
    return;
  }
  for (uint_fast8_t i = 0; i < pieces.size(); ++i) {
    const auto piece = pieces[i];
    for (const auto shape : piece) {
      for (uint_fast8_t x = 0; x < 7; ++x) {
        for (uint_fast8_t y = 0; y < 7; ++y) {
          if (can_place(shape, x, y)) {
            place(shape, x, y);
            backtrack(placed + 1, pieces.subspan(i + 1));
            unplace(shape, x, y);
          }
        }
      }
    }
  }
}

} // namespace

int main() {
  std::ios::sync_with_stdio(false);
  backtrack(0, Pieces);
}
