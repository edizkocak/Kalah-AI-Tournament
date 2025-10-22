#pragma once

#include "heuristics.hpp"

#define NAMESPACE_MINMAX_BEGIN namespace Minmax {
#define NAMESPACE_MINMAX_END }

NAMESPACE_MINMAX_BEGIN

inline Heuristic search(Kalah kalah, Depth depth, Player player, Move move) {
    // current mvoe
    bool again = kalah.play(player, move);
    player = again ? player : !player;
    depth += again;

    // recursion end
    if (kalah.isFinal(player)) return kalah.finalize();
    if (--depth == 0) return Heuristics::heuristic(kalah, player);

    // next move
    Heuristic best = LOSE[player];
    for (move = 0; move < kalah.size; ++move) {
        if (!kalah.isValid(player, move)) continue;
        Heuristic next = search(kalah, depth, player, move);
        best = better(player, best, next);
    }
    return best;
}

inline Result st(Kalah kalah, Depth depth) {
    //std::cerr << "\n\nDepth: " << size_t(depth) << "\n";
    Heuristic best = std::numeric_limits<Heuristic>::min();
    Move move;
    for (Move m = 0; m < kalah.size; ++m) {
        if (!kalah.isValid(SOUTH, m)) continue;
        Heuristic next = search(kalah, depth, SOUTH, m);
        //std::cerr << "  " << size_t(m) << ": " << next << std::endl;
        if (next > best) {
            best = next;
            move = m;
        }
    }
    return { move, best };
}

NAMESPACE_MINMAX_END