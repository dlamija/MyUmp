#include "umpsetting.h"
#include "ui_umpsetting.h"

UMPSetting::UMPSetting(UserProfile *user, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::UMPSetting)
{
    ui->setupUi(this);
    this->user = user;
}

UMPSetting::~UMPSetting()
{
    delete ui;
}

void UMPSetting::setSettingUI()
{
    ui->username->setText(user->userName);
    ui->password->setText(user->userPass);


    if (user->autoCheckIn == true){
        ui->checkBoxCheckINAuto->setCheckState(Qt::Checked);
    }

    if (user->disableCheckOut == true){
        ui->checkBoxCheckOutBefore4pm->setCheckState(Qt::Checked);
    }

    if(user->disableOutside == true){
        ui->checkBoxDisableOutside->setCheckState(Qt::Checked);
    }
}

