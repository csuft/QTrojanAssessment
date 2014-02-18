#include "trojanassessment.h"
#include <QtWidgets/QApplication>
#include <QStyleFactory>

#define QT_NO_CAST_FROM_ASCII

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	/* set up the basic information for application */
	app.setOrganizationName(QStringLiteral("HUST"));
	app.setApplicationName(QStringLiteral("TrojanDetector"));
	app.setApplicationVersion(QStringLiteral("1.0-alpha"));
	QApplication::setStyle(QStyleFactory::create(QStringLiteral("Fusion")));
	// To add a splash screen.

	/* Create the main window */
	TrojanAssessment win;
	win.show();
	return app.exec();
}
