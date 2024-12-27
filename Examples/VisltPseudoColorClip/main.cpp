#include "VisltDemo.h"

#include <QApplication>

int main(int argc, char* argv[])
{
	QApplication app(argc, argv);
	VisltDemoWindow w;
	w.show();
	return app.exec();
}