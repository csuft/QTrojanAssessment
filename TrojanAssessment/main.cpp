#include "trojanassessment.h"
#include <QtWidgets/QApplication>
#include <QStyleFactory>

#define QT_NO_CAST_FROM_ASCII
#pragma comment(lib, "chartdir51.lib")

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	/* set up the basic information for application */
	app.setOrganizationName(QStringLiteral("HUST"));
	app.setApplicationName(QStringLiteral("TrojanDetector"));
	app.setApplicationVersion(QStringLiteral("1.0-alpha"));
	QApplication::setStyle(QStyleFactory::create(QStringLiteral("Fusion")));

	/* Create the main window */
	TrojanAssessment win;
	win.show();
	return app.exec();
}
