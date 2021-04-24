#ifndef BUBBLESORTMODEL_H
#define BUBBLESORTMODEL_H

#include "sortmodel.h"
#include <QObject>

class BubbleSortModel : public SortModel {
	Q_OBJECT
	public:
		BubbleSortModel(QObject *parent = nullptr): SortModel(parent) {}

	public slots:
		virtual void step() override {
			if (isFinished())
				return;

			switch(std::get<0>(lastAction())) {
				case SortAction::Start:
				case SortAction::Swap:
					compareStep();
				break;

				case SortAction::Compare:
					swapStep();
				break;

				case SortAction::None:
				break;
			}
			if (std::get<0>(lastAction()) == SortAction::None) {
				compareStep();
			}
		}

		virtual void setArray(const Array &array) {
			SortModel::setArray(array);
			i = 0;
			j = 0;
		}

	private:
		void compareStep() {
			if (j >= array().size() - i - 1) {
				if (!swapped) {
					finish();
					return;
				}

				i += 1;
				j = 0;
			}
			if (i >= array().size()) {
				finish();
				return;
			}

			compare(j + 1, j);
		}

		void swapStep() {
			if (compareResult()) {
				swap(j, j + 1);
				swapped = true;
			}
			else {
				nop();
			}
			j += 1;
		}

		bool swapped = false;
		uint i = 0, j = 0;
};

#endif // BUBBLESORTMODEL_H
