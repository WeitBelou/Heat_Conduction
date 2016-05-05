#include <QApplication>

#include "gui/mainwindow.h"

int main(int argc, char **argv)
{
	QApplication app(argc, argv);

	MainWindow e;
	e.show();

	return app.exec();
}
