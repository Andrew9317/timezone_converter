#include "RoundedDialog.hpp"

#include <QMouseEvent>
#include <QPainter>
#include <QStyleOption>

RoundedDialog::RoundedDialog(QWidget* parent)
    : QDialog(parent)
    , m_borderWidth(-1)
    , m_borderRadius(0)
    , m_mousePressed(false)
    , m_mousePosition(QPoint())
{
    // The FramelessWindowHint flag and WA_TranslucentBackground attribute are vital.
    setWindowFlags(windowFlags() | Qt::FramelessWindowHint | Qt::WindowSystemMenuHint);
    setAttribute(Qt::WA_TranslucentBackground);
}

void RoundedDialog::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        this->m_mousePressed = true;
        this->m_mousePosition = event->pos();
    }
}

void RoundedDialog::mouseMoveEvent(QMouseEvent* event)
{
    if (this->m_mousePressed)
    {
        this->move(this->mapToParent(event->pos() - this->m_mousePosition));
    }
}

void RoundedDialog::mouseReleaseEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        this->m_mousePressed = false;
        this->m_mousePosition = QPoint();
    }
}

void RoundedDialog::paintEvent(QPaintEvent*)
{
    if (!(windowFlags() & Qt::FramelessWindowHint) && !testAttribute(Qt::WA_TranslucentBackground))
    {
        return; // nothing to do
    }

    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);

    // Test for a style sheet. If so then let that take over.
    if (testAttribute(Qt::WA_StyleSheetTarget))
    {
        QStyleOption opt;
        opt.initFrom(this);
        style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
        p.end();
        return;
    }

    QRectF rect(QPointF(0, 0), size());

    // Check for a border size.
    double penWidth = m_borderWidth;

    if (penWidth < 0.0)
    {
        QStyleOption opt;
        opt.initFrom(this);
        penWidth = style()->pixelMetric(QStyle::PM_DefaultFrameWidth, &opt, this);
    }

    if (penWidth > 0.0)
    {
        p.setPen(QPen(palette().brush(foregroundRole()), penWidth));
        // Ensure border fits inside the available space.
        const double dlta = penWidth * 0.5;
        rect.adjust(dlta, dlta, -dlta, -dlta);
    }
    else
    {
        // QPainter comes with a default 1px pen when initialized on a QWidget.
        p.setPen(Qt::NoPen);
    }

    // Set the brush from palette role.
    p.setBrush(palette().brush(backgroundRole()));

    // Draw a quicker rec if there is no radius.
    if (m_borderRadius > 0.0)
    {
        p.drawRoundedRect(rect, m_borderRadius, m_borderRadius, Qt::AbsoluteSize);
    }
    else
    {
        p.drawRect(rect);
    }

    p.end();
}