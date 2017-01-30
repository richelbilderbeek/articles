#include "qtdialog.h"
#include "qtwidget.h"

QtDialog::QtDialog(QWidget *parent)
  : QDialog(parent),
    m_widget1(new QtWidget(this)),
    m_widget2(new QtWidget(this))
{
  m_widget1->setGeometry( 0,0,32,32);
  m_widget2->setGeometry(32,0,32,32);
}
