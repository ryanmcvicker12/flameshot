
#pragma once
#include <QGraphicsDropShadowEffect>
#include <QWidget>

class QVBoxLayout;
class QLabel;

class MediaWidget: public QWidget
{
    Q_OBJECT
public:
    explicit MediaWidget(const QPixmap& pixmap, QWidget* parent = nullptr);

    int margin() const;

protected:
    void wheelEvent(QWheelEvent* e);
    void mouseDoubleClickEvent(QMouseEvent*);
    void mousePressEvent(QMouseEvent*);
    void mouseMoveEvent(QMouseEvent*);
    void enterEvent(QEvent*);
    void leaveEvent(QEvent*);

private:
    void setScaledPixmap(const QSize& size);

    QPixmap m_pixmap;
    QVBoxLayout* m_layout;
    QLabel* m_label;
    QPoint m_dragStart;
    qreal m_offsetX, m_offsetY;
    QGraphicsDropShadowEffect* m_shadowEffect;
    QColor m_baseColor, m_hoverColor;
};
