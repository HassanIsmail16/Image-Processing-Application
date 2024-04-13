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

    void on_blackAndWhiteBtn_clicked();

    void on_invertBtn_clicked();

    void on_edgeDetectionBtn_clicked();

    void on_warmBtn_clicked();

    void on_oilBtn_clicked();

    void on_infraredBtn_clicked();

    void on_darkenAndLightenBtn_clicked();

    void on_darkenBtn_clicked();

    void on_lightenBtn_clicked();

    void on_darkenSlider_valueChanged(int value);

    void on_darkenApplyBtn_clicked();

    void on_lightenSlider_valueChanged(int value);

    void on_lightenApplyBtn_clicked();

    void on_blurSlider_valueChanged(int value);

    void on_blurApplyBtn_clicked();

    void on_blurBtn_clicked();

    void on_globalBackBtn_clicked();

    void updateStyleSheet();

    void on_saveImage_clicked();

    void on_loadImage_clicked();

    void on_rotateBtn_clicked();

    void on_rotate90_clicked();

    void on_rotate180_clicked();

    void on_rotate270_clicked();

    void on_skewBtn_clicked();

    void on_skewAngleSlider_valueChanged(int value);

    void on_skewApplyBtn_clicked();

private:
    Ui::MainWindow *ui;

    QTimer *timer;
};
#endif // MAINWINDOW_H
