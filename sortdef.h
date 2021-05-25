#ifndef SORTDEF_H
#define SORTDEF_H

#include <Qt>
#include <vector>
#include <tuple>

using Array = std::vector <uint>;

enum class SortAction {
    Start, Swap, Compare
};

using ActionResult = std::tuple <SortAction, uint, uint>;

#endif // SORTDEF_H
