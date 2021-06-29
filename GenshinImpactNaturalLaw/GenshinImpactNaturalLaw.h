#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_GenshinImpactNaturalLaw.h"

class GenshinImpactNaturalLaw : public QMainWindow
{
    Q_OBJECT

public:
    GenshinImpactNaturalLaw(QWidget *parent = Q_NULLPTR);

private:
    Ui::GenshinImpactNaturalLawClass ui;
};
