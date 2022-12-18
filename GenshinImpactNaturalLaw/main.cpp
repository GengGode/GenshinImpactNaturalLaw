#include "GenshinImpactNaturalLaw.h"
#include <QtWidgets/QApplication>
#include "SingleApplication.h"

int main(int argc, char *argv[])
{
	// -v 输出版本号
	if (argc > 1 && strcmp(argv[1], "-v") == 0)
	{
		printf("%s\n", tl::launcher::version::version);
		return 0;
	}
	// -V 输出完整编译号 
	if (argc > 1 && strcmp(argv[1], "-V") == 0)
	{
		printf("%s\n", tl::launcher::version::build_version);
		return 0;
	}


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
