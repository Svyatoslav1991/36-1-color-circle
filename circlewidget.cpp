#include "circlewidget.h"
#include <QPainter>

CircleWidget::CircleWidget(QWidget *parent) : QWidget(parent)
{
    m_color = Color::green;
    m_circle.load(":/images/images/greenCircle.png");
}

//---------------------------------------------------------------------------------------

void CircleWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawImage(QRectF(0, 0, this->width(), this->height()), m_circle);

    Q_UNUSED(event)
}

//----------------------------------------------------------------------------------------

void CircleWidget::sliderValueChanged(int value)
{
    if(value < 34)
    {
        if(m_color != Color::green)
        {
            m_color = Color::green;
            m_circle.load(":/images/images/greenCircle.png");
            this->repaint();
            emit changeImage();
        }
    }
    else if(value > 66)
    {
        if(m_color != Color::red)
        {
            m_color = Color::red;
            m_circle.load(":/images/images/redCircle.png");
            this->repaint();
            emit changeImage();
        }
    }
    else
    {
        if(m_color != Color::yellow)
        {
            m_color = Color::yellow;
            m_circle.load(":/images/images/yellowCircle.png");
            this->repaint();
            emit changeImage();
        }
    }
}

//----------------------------------------------------------------------------------------

void CircleWidget::resizeEvent(QResizeEvent *event)
{
    this->repaint();

    Q_UNUSED(event)
}

//----------------------------------------------------------------------------------------

void CircleWidget::mousePressEvent(QMouseEvent *event)
{
    m_circle.load(":/images/images/blackCircle.png");
    emit changeImage();
    this->repaint();

    Q_UNUSED(event);
}

//----------------------------------------------------------------------------------------

void CircleWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if(m_color == Color::green)
    {
        m_circle.load(":/images/images/greenCircle.png");
    }
    else if(m_color == Color::red)
    {
        m_circle.load(":/images/images/redCircle.png");
    }
    else
    {
        m_circle.load(":/images/images/yellowCircle.png");
    }
    this->repaint();

    Q_UNUSED(event);
}
