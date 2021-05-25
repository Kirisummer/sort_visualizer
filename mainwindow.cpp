#include "mainwindow.h"

#include <QGridLayout>

#include "bubblesortmodel.h"
#include "insertsortmodel.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	addModel(new BubbleSortModel, ui->leftView);
	addModel(new InsertSortModel, ui->rightView);
	connect(this, &MainWindow::destroyed, ui->control, &SortControl::reset);
	ui->control->reset();
}

void MainWindow::addModel(SortModel *model, SortView *view) {
	connect(model, &SortModel::finished, ui->control, &SortControl::stop);
	connect(ui->control, &SortControl::step, model, &SortModel::step);
	connect(ui->control, &SortControl::setArray, model, &SortModel::run);

	connect(model, &SortModel::reset, view, &SortView::setArray);
	connect(model, &SortModel::swapped, view, &SortView::swap);
	connect(model, &SortModel::compared, view, &SortView::compare);

	model->setParent(this);
}
