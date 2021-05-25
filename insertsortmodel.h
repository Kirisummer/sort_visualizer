#ifndef INSERTSORTMODEL_H
#define INSERTSORTMODEL_H

#include "sortmodel.h"
#include <QObject>


class InsertSortModel : public SortModel {
	Q_OBJECT
	public:
		explicit InsertSortModel(QObject *parent = nullptr):
			SortModel(parent) {}

	protected:
		virtual void sort() override;
};

#endif // INSERTSORTMODEL_H
