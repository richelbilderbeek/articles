#include "qtwidget.h"

QtWidget::QtWidget(QWidget *parent) :
  QPushButton(parent),
  m_count(0)
{

}

void QtWidget::mousePressEvent(QMouseEvent *)
{
  ++m_count;
  this->setText(QString::number(m_count));
}

