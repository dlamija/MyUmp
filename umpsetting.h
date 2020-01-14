#ifndef UMPSETTING_H
#define UMPSETTING_H

#include <QDialog>
#include "userprofile.h"

QT_BEGIN_NAMESPACE
namespace Ui { class UMPSetting; }
QT_END_NAMESPACE

class UMPSetting : public QDialog
{
    Q_OBJECT

public:
    UMPSetting(UserProfile *user, QWidget *parent = nullptr);
    ~UMPSetting();

private slots:
    void on_pushButtonSave_clicked();

    void on_pushButtonDelete_clicked();

private:
    Ui::UMPSetting *ui;
    UserProfile *user;
    void setSettingUI();
};
#endif // UMPSETTING_H
