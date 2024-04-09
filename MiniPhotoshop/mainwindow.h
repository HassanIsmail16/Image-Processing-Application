#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_openImage_clicked();

    void on_grayScaleBtn_clicked();

    void on_effectsBtn_clicked();

    void on_toolsBtn_clicked();

    void on_backBtn_fx_clicked();

    void on_backBtn_tools_clicked();

    void on_blackAndWhiteBtn_clicked();

    void on_invertBtn_clicked();

    void on_edgeDetectionBtn_clicked();

    void on_warmBtn_clicked();

    void on_oilBtn_clicked();

    void on_infraredBtn_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
