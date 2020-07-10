#ifndef UMPSETTING_H
#define UMPSETTING_H

#include <QDialog>
#include "user.h"

QT_BEGIN_NAMESPACE
namespace Ui { class UMPSetting; }
QT_END_NAMESPACE

class UMPSetting : public QDialog
{
    Q_OBJECT

public:
    UMPSetting(User *user, QWidget *parent = nullptr);
    ~UMPSetting();

private slots:
    void on_pushButtonSave_clicked();
    void on_pushButtonDelete_clicked();

    void on_username_textChanged(const QString &arg1);

private:
    Ui::UMPSetting *ui;
    User *user;
    void setSettingUI();

signals:
    void save_delete(bool save);
};
#endif // UMPSETTING_H
