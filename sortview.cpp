#include "ui_sortview.h"
#include "sortview.h"


SortView::SortView(QWidget *parent)
  : QFrame(parent)
  , ui(new Ui::SortView)
  , regularColor(Qt::blue)
  , swapColor(Qt::red)
  , compareColor(Qt::green)
{
	ui->setupUi(this);
}

void SortView::redraw() {
	scene = std::make_unique<QGraphicsScene>(
		0, 0,
		ui->columnView->width() - 10, ui->columnView->height() - 10
	);
	ui->columnView->setScene(scene.get());

	for (uint idx = 0; idx < array.size(); ++idx) {
		if ((lastChanged.first != lastChanged.second)
		&&  (lastChanged.first == idx || lastChanged.second)) {
			switch (lastAction) {
				case SortAction::Swap:
					drawColumn(idx, swapColor);
				break;
				case SortAction::Compare:
					drawColumn(idx, compareColor);
				break;
				default:
					drawColumn(idx, regularColor);
			}
		}
		else
			drawColumn(idx, regularColor);
	}
}

void SortView::setArray(const Array &array) {
	lastChanged = std::make_pair(0, 0);
	lastAction = SortAction::Start;

	auto min_max = std::minmax_element(array.begin(), array.end());
	min = *min_max.first;
	max = *min_max.second;

	this->array = array;
	columns.clear();
	columns.resize(array.size());

	ui->swapsAmountLabel->setText("0");
	ui->compAmountLabel->setText("0");

	redraw();
}

void SortView::swap(uint i, uint j) {
	std::swap(array[i], array[j]);

	if (lastChanged.first != lastChanged.second) {
		redrawColumn(lastChanged.first, regularColor);
		redrawColumn(lastChanged.second, regularColor);
	}
	lastChanged = std::make_pair(i, j);
	redrawColumn(i, swapColor);
	redrawColumn(j, swapColor);

	uint swaps = ui->swapsAmountLabel->text().toUInt();
	ui->swapsAmountLabel->setText(QString::number(swaps	+ 1));
}

void SortView::compare(uint i, uint j) {
	if (lastChanged.first != lastChanged.second) {
		redrawColumn(lastChanged.first, regularColor);
		redrawColumn(lastChanged.second, regularColor);
	}
	lastChanged = std::make_pair(i, j);
	redrawColumn(i, compareColor);
	redrawColumn(j, compareColor);

	uint comps = ui->compAmountLabel->text().toUInt();
	ui->compAmountLabel->setText(QString::number(comps	+ 1));
}

void SortView::resizeEvent(QResizeEvent *event) {
	QFrame::resizeEvent(event);
	redraw();
}

void SortView::drawColumn(uint idx, const QColor &color) {
	qreal height = columnHeight() * array.at(idx);
	qreal width = columnWidth();

	columns[idx] = scene->addRect(QRectF(
		width * idx,
		0,
		width,
		height
	), QPen(color), QBrush(color));
}

void SortView::removeColumn(uint idx) {
	auto item = columns.at(idx);
	if (item) {
		scene->removeItem(item);
		delete item;
	}
}

void SortView::redrawColumn(uint idx, const QColor &color) {
	removeColumn(idx);
	drawColumn(idx, color);
}

QGraphicsRectItem *SortView::getColumn(uint idx) const {
	auto item = scene->itemAt(QPointF(columnWidth() * idx, 0), QTransform());
	return dynamic_cast <QGraphicsRectItem *>(item);
}

const qreal SortView::MAX_WIDTH = 20;

qreal SortView::columnHeight() const {
	return (scene->height() - 10) / (max - min);
}

qreal SortView::columnWidth() const {
	return std::min(scene->width() / array.size(), MAX_WIDTH);
}
