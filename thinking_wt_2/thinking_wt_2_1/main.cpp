#include <boost/signals2.hpp>
#include <Wt/WApplication>
#include <Wt/WContainerWidget>
#include <Wt/WEnvironment>
#include <Wt/WPaintDevice>
#include <Wt/WPaintedWidget>
#include <Wt/WPainter>
#include <Wt/WPushButton>
#include "tictactoe.h"
//---------------------------------------------------------------------------
struct WtTicTacToeWidget : public Wt::WPaintedWidget
{
  WtTicTacToeWidget()
  {
    this->resize(32,32);
  }
  protected:
  void paintEvent(Wt::WPaintDevice *paintDevice)
  {
    Wt::WPainter painter(paintDevice);
    painter.drawImage(0,0,Wt::WPainter::Image("R.png",32,32));
  }

  private:
  TicTacToe m_tictactoe;
};
//---------------------------------------------------------------------------
struct WtTicTacToeDialog : public Wt::WContainerWidget
{
  WtTicTacToeDialog()
  : m_tictactoe(new WtTicTacToeWidget)
  {
    this->addWidget(m_tictactoe);
  }
  private:
  WtTicTacToeWidget * const m_tictactoe;
};
//---------------------------------------------------------------------------
struct WtApplication : public Wt::WApplication
{
  WtApplication(const Wt::WEnvironment& env)
    : Wt::WApplication(env),
    m_dialog(new WtTicTacToeDialog)
  {
    this->setTitle("Thinking Wt 2: creating a TicTacToe widget");
    root()->addWidget(m_dialog);
  }
  private:
  WtTicTacToeDialog * const m_dialog;
};
//---------------------------------------------------------------------------
Wt::WApplication *createApplication(
  const Wt::WEnvironment& env)
{
  return new WtApplication(env);
}
//---------------------------------------------------------------------------
int main(int argc, char **argv)
{
  return WRun(argc, argv, &createApplication);
}
//---------------------------------------------------------------------------
