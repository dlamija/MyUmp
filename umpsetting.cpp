#include "umpsetting.h"
#include "myump.h"
#include "ui_umpsetting.h"
#include <QDebug>
#include <QSettings>

UMPSetting::UMPSetting(User *user, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::UMPSetting)
{
    ui->setupUi(this);
    this->user = user;
    this->setSettingUI();

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
    }else {
        ui->checkBoxCheckINAuto->setCheckState(Qt::Unchecked);
    }
    if (user->disableCheckOut == true){
        ui->checkBoxCheckOutBefore4pm->setCheckState(Qt::Checked);
    }else {
        ui->checkBoxCheckOutBefore4pm->setCheckState(Qt::Unchecked);
    }
    if(user->disableOutside == true){
        ui->checkBoxDisableOutside->setCheckState(Qt::Checked);
    }else{
        ui->checkBoxDisableOutside->setCheckState(Qt::Unchecked);
    }
}


void UMPSetting::on_pushButtonSave_clicked()
{
    user->userName = ui->username->text();
    user->userPass = ui->password->text();
    user->autoCheckIn = ui->checkBoxCheckINAuto->checkState();
    user->disableCheckOut = ui->checkBoxCheckOutBefore4pm->checkState();
    user->disableOutside = ui->checkBoxDisableOutside->checkState();
    UMPSetting::hide();
    this->valueChanged();
}

void UMPSetting::on_pushButtonDelete_clicked()
{
    user->userName = "";
    user->userPass = "";
    user->autoCheckIn = false;
    user->disableCheckOut = false;
    user->disableOutside = false;

    QSettings settings;
    settings.beginGroup("Login");
        settings.remove("");
    settings.endGroup();
    ui->pushButtonSave->setDisabled(true);
    this->setSettingUI();
    //UMPSetting::hide();
}

void UMPSetting::on_username_textChanged(const QString &arg1)
{
    ui->pushButtonSave->setEnabled(true);
}
