#include "mainwindowconfigurationrondier.h"
#include "ui_mainwindowconfigurationrondier.h"

MainWindowConfigurationRondier::MainWindowConfigurationRondier(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindowConfigurationRondier)
{
    ui->setupUi(this);
}

MainWindowConfigurationRondier::~MainWindowConfigurationRondier()
{
    delete ui;
}
