#include "umpsetting.h"
#include "ui_umpsetting.h"

UMPSetting::UMPSetting(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::UMPSetting)
{
    ui->setupUi(this);
}

UMPSetting::~UMPSetting()
{
    delete ui;
}

