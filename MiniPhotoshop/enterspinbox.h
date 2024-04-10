#ifndef ENTERSPINBOX_H
#define ENTERSPINBOX_H

#include <QSpinBox>
#include <QKeyEvent>

class EnterSpinBox : public QSpinBox {
    Q_OBJECT
public:
    EnterSpinBox(QWidget *parent = nullptr);

protected:
    void keyPressEvent(QKeyEvent *event) override;
};

#endif // ENTERSPINBOX_H
