#include "Dungeon.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Dungeon w;
	w.show();
	return a.exec();
}
