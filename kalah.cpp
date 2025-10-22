#include <sstream>
#include <chrono>
#include "kalah.hpp"
#include "minmax.hpp"


inline constexpr Depth MIN_DEPTH = 4;
inline constexpr Depth MAX_DEPTH = 16;

static_assert(MIN_DEPTH > 0);
static_assert(MAX_DEPTH >= MIN_DEPTH);


int main(int argc, char* argv[]) {
    Kalah kalah;
    if (argc == 1) {
        std::cin >> kalah;
    } else {
        std::stringstream ss;
        ss << argv[1];
        ss >> kalah;
    }

    for (Depth depth = MIN_DEPTH; depth <= MAX_DEPTH; ++depth) {
        auto begin = std::chrono::steady_clock::now();
        auto [move, h] = Minmax::st(kalah, depth);
        auto end = std::chrono::steady_clock::now();
        std::cout << size_t(move) << " " << h << std::endl;
        //std::cerr << size_t(depth) << ": " << (end - begin).count() / 1000 / 1000.0 << "ms -> " << size_t(move) << std::endl;
    }

}