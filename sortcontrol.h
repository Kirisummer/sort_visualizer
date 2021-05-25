#ifndef SORTCONTROL_H
#define SORTCONTROL_H

#include "sortdef.h"
#include "ui_sortcontrol.h"

#include <QTimer>
#include <QFrame>


namespace Ui {
	class sortcontrol;
}

class SortControl : public QFrame {
	Q_OBJECT
	public:
		explicit SortControl(QWidget *parent = nullptr);
		~SortControl() { delete ui; }

	public slots:
		void reset();
		void doStep();
		void sort();
		void stop();

	signals:
		void step();
		void setArray(const Array &array);

	private:
		Ui::sortcontrol *ui;
		QTimer timer;
};

#endif // SORTCONTROL_H
