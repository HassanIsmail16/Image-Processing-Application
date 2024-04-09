#ifndef SCALEDLABEL_H
#define SCALEDLABEL_H

#include <QLabel>

class ScaledLabel : public QLabel {
    Q_OBJECT
public:
    ScaledLabel(QWidget *parent = nullptr);

protected:
    void resizeEvent(QResizeEvent *event) override;

private:
    void scaleImage();
};

#endif // SCALEDLABEL_H
