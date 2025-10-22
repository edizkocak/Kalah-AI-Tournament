#pragma once

#include "kalah.hpp"

#define NAMESPACE_HEURISTICS_BEGIN namespace Heuristics {
#define NAMESPACE_HEURISTICS_END }

NAMESPACE_HEURISTICS_BEGIN

inline Heuristic heuristic(Kalah kalah, Player player) {
    Heuristic h = Heuristic(kalah.kalahs[SOUTH]) - Heuristic(kalah.kalahs[NORTH]);


    return h;
}

NAMESPACE_HEURISTICS_END
