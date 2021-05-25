#include "insertsortmodel.h"


void InsertSortModel::sort() {
	for (uint i = 1; i < array().size(); ++i) {
		for (uint j = i; j > 0; --j) {
			std::optional <bool> less = compare(j, j - 1);
			if (!less.has_value())
				return;
			if (!less.value())
				break;
			if (less.value()) {
				bool abort = swap(j, j -1);
				if (abort)
					return;
			}
		}
	}

	finish();
}
