#include "GenshinImpactNaturalLaw.h"
#include <QtWidgets/QApplication>
#include "SingleApplication.h"

int main(int argc, char *argv[])
{
    //QApplication a(argc, argv);

	SingleApplication a(argc, argv, "TianLi Launcher UniqueKey");
	if (a.isRunning())
	{
		a.sendMessage("TianLi Launcher Is Running");
		return 0;
	}
	QTranslator translator;
	translator.load(":/QtWidgetsSetting/genshinimpactnaturallaw_zh.qm");
	a.installTranslator(&translator);

	GenshinImpactNaturalLaw w;

	QObject::connect(&a, &SingleApplication::messageAvailable, &w, &GenshinImpactNaturalLaw::ReceiveUniqueKeyMsg);

    w.show();
    return a.exec();
}
