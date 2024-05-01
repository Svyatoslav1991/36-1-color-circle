#ifndef CIRCLEWIDGET_H
#define CIRCLEWIDGET_H

#include <QWidget>
#include <QImage>

class CircleWidget : public QWidget
{
    Q_OBJECT

private:
    QImage m_circle;
    enum class Color {green, yellow, red};
    Color m_color;

public:
    explicit CircleWidget(QWidget *parent = nullptr);

signals:
    void changeImage();
    // QWidget interface
protected:
    virtual void paintEvent(QPaintEvent *event);

private slots:
    void sliderValueChanged(int value);
    virtual void resizeEvent(QResizeEvent *event);

    // QWidget interface
protected:
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
};

#endif // CIRCLEWIDGET_H
