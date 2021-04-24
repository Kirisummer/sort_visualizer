#ifndef SORTVIEW_H
#define SORTVIEW_H

#include "sortdef.h"
#include "ui_sortview.h"

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <memory>

namespace Ui {
	class SortView;
}

class SortView : public QFrame {
	Q_OBJECT

	public:
		explicit SortView(QWidget *parent = nullptr);

	public slots:
		void redraw();
		void setArray(const Array &);
		void swap(uint, uint);
		void compare(uint, uint);

	protected:
		virtual void resizeEvent(QResizeEvent *event) override;

		void drawColumn(uint idx, const QColor &color);
		void removeColumn(uint idx);
		void redrawColumn(uint idx, const QColor &color);
		QGraphicsRectItem *getColumn(uint idx) const;

		qreal columnHeight() const;
		qreal columnWidth() const;

	private:
		std::unique_ptr<Ui::SortView> ui;
		std::unique_ptr<QGraphicsScene> scene;
		std::vector <QGraphicsRectItem *> columns;

		static const qreal MAX_WIDTH;
		uint min, max;
		Array array;

		std::pair <uint, uint> lastChanged;

		QColor regularColor, swapColor, compareColor;
};

#endif // SORTVIEW_H
