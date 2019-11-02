#include "Builder.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Builder w;
	w.show();
	return a.exec();
}
