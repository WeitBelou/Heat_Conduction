#include <QApplication>

#include "editor/mainwindow.h"

int main(int argc, char **argv)
{
	QApplication app(argc, argv);

	MainWindow e;
	e.show();

	return app.exec();
}
