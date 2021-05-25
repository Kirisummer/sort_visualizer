#ifndef BUBBLESORTMODEL_H
#define BUBBLESORTMODEL_H

#include "sortmodel.h"
#include <QObject>


class BubbleSortModel : public SortModel {
	Q_OBJECT
	public:
		explicit BubbleSortModel(QObject *parent = nullptr):
			SortModel(parent) {}
	protected:
		virtual void sort() override;
};

#endif // BUBBLESORTMODEL_H
