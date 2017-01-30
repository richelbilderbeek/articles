#ifndef QTDIALOG_H
#define QTDIALOG_H

#include <QDialog>

struct QtWidget;

class QtDialog : public QDialog
{
  Q_OBJECT

public:
  explicit QtDialog(QWidget *parent = 0);

private:
  QtWidget * const m_widget1;
  QtWidget * const m_widget2;
};

#endif // QTDIALOG_H
