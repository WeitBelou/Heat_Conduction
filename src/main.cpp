#include <QApplication>

#include "editor/editor.h"

int main(int argc, char **argv)
{
	QApplication app(argc, argv);

	Editor e;
	e.show();

	return app.exec();
}