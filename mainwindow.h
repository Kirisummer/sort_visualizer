#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"

#include <QMainWindow>
#include <memory>

#include "sortcontrol.h"
#include "sortview.h"
#include "sortmodel.h"


class MainWindow : public QMainWindow {
	Q_OBJECT
	public:
		explicit MainWindow(QWidget *parent = nullptr);

	protected:
		void addModel(SortModel *model, SortView *view);

	private:
		std::unique_ptr<Ui::MainWindow> ui;

};

#endif // MAINWINDOW_H
