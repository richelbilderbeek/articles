#include <boost/signals2.hpp>
#include <Wt/WApplication>
#include <Wt/WBreak>
#include <Wt/WContainerWidget>
#include <Wt/WEnvironment>
#include <Wt/WEvent>
#include <Wt/WPaintDevice>
#include <Wt/WPaintedWidget>
#include <Wt/WPainter>
#include <Wt/WPushButton>
#include "tictactoe.h"

struct WtTicTacToeWidget : public Wt::WPaintedWidget
{
  WtTicTacToeWidget()
  {
    this->resize(32,32);
  }
  boost::signals2::signal<void ()> m_signal_state_changed;

  int GetState() const { return 0; }
  void Restart() {}
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
  : m_button(new Wt::WPushButton),
    m_tictactoe(new WtTicTacToeWidget)
  {
    this->addWidget(m_tictactoe);
    this->addWidget(new Wt::WBreak(this));
    this->addWidget(m_button);
    m_button->setText("Restart");
    m_tictactoe->m_signal_state_changed.connect(
      boost::bind(
        &WtTicTacToeDialog::OnStateChanged,
        this));
    m_button->clicked().connect(
      this,&WtTicTacToeDialog::OnRestart);
  }
  private:
  Wt::WPushButton * const m_button;
  WtTicTacToeWidget * const m_tictactoe;
  void OnRestart()
  {
    m_tictactoe->Restart();
  }
  void OnStateChanged()
  {
    switch (m_tictactoe->GetState())
    {
      case TicTacToe::player1:
        m_button->setText("Player 1 has won. Click to restart");
        break;
      case TicTacToe::player2:
        m_button->setText("Player 2 has won. Click to restart");
        break;
      case TicTacToe::draw:
        m_button->setText("Draw. Click to restart");
        break;
      case TicTacToe::no_winner:
        m_button->setText("Restart");
        break;
      default:
        assert(!"Should not get here");
        break;
    }
  }
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
