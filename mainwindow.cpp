#include "mainwindow.h"

#include "bubblesortmodel.h"
#include <QGridLayout>

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	addModel(new BubbleSortModel, ui->leftView);
	addModel(new BubbleSortModel, ui->rightView);
	ui->control->reset();
}

void MainWindow::addModel(SortModel *model, SortView *view) {
	connect(model, &SortModel::finished, ui->control, &SortControl::stop);
	connect(ui->control, &SortControl::step, model, &SortModel::step);
	connect(ui->control, &SortControl::setArray, model, &SortModel::setArray);

	connect(model, &SortModel::arraySet, view, &SortView::setArray);
	connect(model, &SortModel::swapped, view, &SortView::swap);
	connect(model, &SortModel::compared, view, &SortView::compare);

	model->setParent(this);
}
