#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_exportButton_clicked();

    void on_searchUserButton_clicked();

    void on_searchLoginButton_clicked();

    void on_exportSettingButton_clicked();

    void on_addUserButton_clicked();

    void on_delUserButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
