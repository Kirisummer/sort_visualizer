#include "bubblesortmodel.h"


void BubbleSortModel::sort() {
	for (uint i = 0; i < array().size(); ++i) {
		bool swapped = false;
		for (uint j = 0; j < array().size() - i - 1; ++j) {
			std::optional <bool> less = compare(j + 1, j);
			if (!less.has_value())
				return;

			if (less.value()) {
				bool abort = swap(j, j + 1);
				if (abort)
					return;
				swapped = true;
			}
		}
		if (!swapped)
			break;
	}

	finish();
}
