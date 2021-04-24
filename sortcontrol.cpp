#include "sortcontrol.h"
#include "ui_sortcontrol.h"

#include <QRandomGenerator>

SortControl::SortControl(QWidget *parent)
	: QFrame(parent)
	, ui(new Ui::sortcontrol)
	, timer(this)
{
	ui->setupUi(this);
	connect(&timer, &QTimer::timeout, this, &SortControl::doStep);

	connect(ui->resetButton, &QPushButton::clicked, this, &SortControl::reset);
	connect(ui->stepButton, &QPushButton::clicked, this, &SortControl::doStep);
	connect(ui->sortButton, &QPushButton::clicked, this, &SortControl::sort);
	connect(ui->stopButton, &QPushButton::clicked, this, &SortControl::stop);
}

void SortControl::reset() {
	quint32 array_size = ui->arraySizeInput->value();
	Array array(array_size);
	std::generate(array.begin(), array.end(), [array_size]() {
		return QRandomGenerator::global()->bounded(array_size) + 1;
	});
	emit setArray(array);
}

void SortControl::doStep() {
	emit step();
}

void SortControl::sort() {
	ui->sortButton->setEnabled(false);
	ui->stepButton->setEnabled(false);
	ui->resetButton->setEnabled(false);
	ui->arraySizeInput->setEnabled(false);
	ui->delayInput->setEnabled(false);
	ui->stopButton->setEnabled(true);

	uint delay = ui->delayInput->value();
	timer.start(delay);
}

void SortControl::stop() {
	ui->sortButton->setEnabled(true);
	ui->stepButton->setEnabled(true);
	ui->resetButton->setEnabled(true);
	ui->arraySizeInput->setEnabled(true);
	ui->delayInput->setEnabled(true);
	ui->stopButton->setEnabled(false);

	timer.stop();
}
