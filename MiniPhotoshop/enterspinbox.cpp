#include "enterspinbox.h"

EnterSpinBox::EnterSpinBox(QWidget *parent) : QSpinBox(parent) {}

void EnterSpinBox::keyPressEvent(QKeyEvent *event) {
    switch (event->key()) {
    case Qt::Key_Up:
    case Qt::Key_Down:
    case Qt::Key_Left:
    case Qt::Key_Right:
        // Allow arrow keys to change the value
        QSpinBox::keyPressEvent(event);
        break;
    case Qt::Key_Return:
    case Qt::Key_Enter:
        // If Enter key is pressed, emit editingFinished signal
        emit editingFinished();
        break;
    default:
        // Ignore all other key events
        break;
    }
}
