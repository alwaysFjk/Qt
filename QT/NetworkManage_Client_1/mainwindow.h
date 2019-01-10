#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDateTime>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected slots:
    void slot_updateTime();

private slots:
    void on_loginButton_clicked();

    void on_logoutButton_clicked();

private:
    Ui::MainWindow *ui;
    QDateTime m_loginDateTime;

};

#endif // MAINWINDOW_H
