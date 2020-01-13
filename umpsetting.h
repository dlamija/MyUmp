#ifndef UMPSETTING_H
#define UMPSETTING_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class UMPSetting; }
QT_END_NAMESPACE

class UMPSetting : public QDialog
{
    Q_OBJECT

public:
    UMPSetting(QWidget *parent = nullptr);
    ~UMPSetting();

private:
    Ui::UMPSetting *ui;
};
#endif // UMPSETTING_H
