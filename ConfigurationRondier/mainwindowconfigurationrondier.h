#ifndef MAINWINDOWCONFIGURATIONRONDIER_H
#define MAINWINDOWCONFIGURATIONRONDIER_H

#include <QMainWindow>

namespace Ui {
class MainWindowConfigurationRondier;
}

class MainWindowConfigurationRondier : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindowConfigurationRondier(QWidget *parent = 0);
    ~MainWindowConfigurationRondier();

private:
    Ui::MainWindowConfigurationRondier *ui;
};

#endif // MAINWINDOWCONFIGURATIONRONDIER_H
