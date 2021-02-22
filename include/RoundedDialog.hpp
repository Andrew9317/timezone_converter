#ifndef ROUNDEDDIALOG_HPP
#define ROUNDEDDIALOG_HPP

#include <QDialog>

class RoundedDialog : public QDialog
{
    Q_OBJECT

    //-1 : use style hint frame width; 0 : no border; > 0 : use this width.
    double m_borderWidth;
    // Desired radius in absolute pixels.
    double m_borderRadius;

    bool m_mousePressed;
    QPoint m_mousePosition;

  public:
    // This class must have a style sheet set with the border-radius
    // value to become rounded.
    explicit RoundedDialog(QWidget* parent = nullptr);

  protected:
    virtual void mousePressEvent(QMouseEvent* event) override;
    virtual void mouseMoveEvent(QMouseEvent* event) override;
    virtual void mouseReleaseEvent(QMouseEvent* event) override;

    virtual void paintEvent(QPaintEvent* event) override;
};

#endif