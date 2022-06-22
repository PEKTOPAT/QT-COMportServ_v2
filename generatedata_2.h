#ifndef GENERATEDATA_2_H
#define GENERATEDATA_2_H

#include <QMainWindow>

namespace Ui {
class GenerateData_2;
}

class GenerateData_2 : public QMainWindow
{
    Q_OBJECT

public:
    explicit GenerateData_2(QWidget *parent = 0);
    ~GenerateData_2();

private:
    Ui::GenerateData_2 *ui;
};

#endif // GENERATEDATA_2_H
