#pragma once

#include <cstdint>
#include <iostream>
#include <limits>

using Move = uint8_t;
using Depth = uint8_t;
using Counter = uint8_t;
using Heuristic = int32_t;
using Player = bool;

inline constexpr Player SOUTH = false;
inline constexpr Player NORTH = true;
inline constexpr Move NO_MOVE = -1;
inline constexpr Move MAX_SIZE = 16;
inline constexpr Heuristic SOUTH_WIN = std::numeric_limits<Heuristic>::max();
inline constexpr Heuristic NORTH_WIN = -SOUTH_WIN;
inline constexpr Heuristic WIN[2] = { SOUTH_WIN, NORTH_WIN };
inline constexpr Heuristic LOSE[2] = { NORTH_WIN, SOUTH_WIN };

struct Result {
    Move move;
    Heuristic h;
};

struct Kalah {
    Move size;
    Counter kalahs[2];
    Counter pits[2][MAX_SIZE];

    inline Kalah(): size(0), kalahs{}, pits{} {}

    inline bool isFinal(Player player) const {
        for (Move m = 0; m < MAX_SIZE; ++m) {
            if (pits[player][m]) return false;
        }
        return true;
    }

    inline bool isValid(Player player, Move move) const {
        return pits[player][move];
    }

    inline Heuristic finalize() {
        for (Move m = 0; m < size; ++m) {
            kalahs[SOUTH] += pits[SOUTH][m];
            pits[SOUTH][m] = 0;
            
            kalahs[NORTH] += pits[NORTH][m];
            pits[NORTH][m] = 0;
        }
        if (kalahs[SOUTH] > kalahs[NORTH]) return SOUTH_WIN;
        if (kalahs[SOUTH] < kalahs[NORTH]) return NORTH_WIN;
        return 0;
    }

    inline bool play(Player player, Move m) {
        Player p = player;
        Counter seeds = pits[p][m];
        pits[p][m] = 0;
        while (seeds--) {
            if (++m == size) {
                if (p == player) {
                    kalahs[p] += 1;
                    m = NO_MOVE;
                    p = !p;
                    continue;
                }
                p = !p;
                m = 0;
            }
            pits[p][m] += 1;
        }
        if (m == NO_MOVE) return true;
        if (p != player) return false;
        if (pits[p][m] != 1) return false;
        pits[p][m] = 0;
        kalahs[p] += 1 + pits[!p][size - 1 - m];
        pits[!p][size - 1 - m] = 0;
        return false;
    }
};

inline std::istream& operator>>(std::istream& is, Kalah& kalah) {
    char ignore;
    size_t v, s, n;
    is >> ignore >> v >> ignore >> s >> ignore >> n >> ignore;
    kalah.size = v;
    kalah.kalahs[0] = s;
    kalah.kalahs[1] = n;
    for (Move m = 0; m < v; ++m) {
        is >> s >> ignore;
        kalah.pits[SOUTH][m] = s;
    }
    for (Move m = 0; m < v; ++m) {
        is >> n >> ignore;
        kalah.pits[NORTH][v - 1 - m] = n;
    }
    return is;
}

inline std::ostream& operator<<(std::ostream& os, const Kalah& kalah) {
    os << '<' << size_t(kalah.size) << ',' << size_t(kalah.kalahs[SOUTH]) << ',' << size_t(kalah.kalahs[NORTH]);
    for (Move m = 0; m < kalah.size; ++m) {
        os << ',' << size_t(kalah.pits[SOUTH][m]);
    }
    for (Move m = 0; m < kalah.size; ++m) {
        os << ',' << size_t(kalah.pits[NORTH][kalah.size - 1 - m]);
    }
    return os << '>';
}

inline Heuristic better(Player player, Heuristic a, Heuristic b) {
    if (player) { // min
        if (a > b) return b;
        return a;
    } else { // max
        if (a > b) return a;
        return b;
    }
}