#include "generatedata_2.h"
#include "ui_generatedata_2.h"

GenerateData_2::GenerateData_2(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GenerateData_2)
{
    ui->setupUi(this);
}

GenerateData_2::~GenerateData_2()
{
    delete ui;
}
