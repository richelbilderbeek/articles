#ifndef QTWIDGET_H
#define QTWIDGET_H

#include <QPushButton>

class QtWidget : public QPushButton
{
    Q_OBJECT
public:
  explicit QtWidget(QWidget *parent = 0);
  void mousePressEvent(QMouseEvent *);

  private:
  int m_count;
};

#endif // QTWIDGET_H
