#include <boost/signals2.hpp>
#include <Wt/WApplication>
#include <Wt/WBreak>
#include <Wt/WBrush>
#include <Wt/WContainerWidget>
#include <Wt/WEnvironment>
#include <Wt/WEvent>
#include <Wt/WPaintDevice>
#include <Wt/WPaintedWidget>
#include <Wt/WPainter>
#include <Wt/WPen>
#include <Wt/WPushButton>
#include "tictactoe.h"

struct WtTicTacToeWidget : public Wt::WPaintedWidget
{
  WtTicTacToeWidget()
  {
    //Without resize, there is nothing to paint on
    this->resize(GetWidth(),GetHeight());
    this->clicked().connect(this,&WtTicTacToeWidget::OnClicked);
    this->update();
  }
  boost::signals2::signal<void ()> m_signal_has_winner;
  boost::signals2::signal<void ()> m_signal_state_changed;

  int GetState() const
  {
    return m_tictactoe.GetWinner();
  }
  void Restart()
  {
    m_tictactoe = TicTacToe();
    this->update();
  }
  protected:
  void paintEvent(Wt::WPaintDevice *paintDevice)
  {
    Wt::WPainter painter(paintDevice);
    const int width  = GetWidth();
    const int height = GetHeight();
    //Set black pen
    Wt::WPen pen = painter.pen();
    pen.setCapStyle(Wt::RoundCap);
    pen.setColor(Wt::WColor(255,255,255));
    painter.setPen(pen);
    painter.setBrush(Wt::WBrush(Wt::WColor(255,255,255)));
    painter.drawRect(0.0,0.0,GetWidth(),GetHeight());
    //Set thick white pen
    pen.setColor(Wt::WColor(0,0,0));
    const int line_width = std::min(width,height) / 15;
    pen.setWidth(line_width);
    painter.setPen(pen);
    //Vertical lines
    painter.drawLine(
        ((1*width)/3)+4,     0+(line_width/2),
        ((1*width)/3)-4,height-(line_width/2));
    painter.drawLine(
        ((2*width)/3)-4,     0+(line_width/2),
        ((2*width)/3)+8,height-(line_width/2));
    //Horizontal lines
    painter.drawLine(
        0+(line_width/2),((1*height)/3)+4,
        width-(line_width/2),((1*height)/3)-4);
    painter.drawLine(
        0+(line_width/2),((2*height)/3)-4,
        width-(line_width/2),((2*height)/3)+8);

    for (int row=0; row!=3; ++row)
    {
      const int x1 = ((row + 0) * (width / 3)) + (line_width/1) + 4;
      const int x2 = ((row + 1) * (width / 3)) - (line_width/1) - 4;
      for (int col=0; col!=3; ++col)
      {
        const int y1 = ((col + 0) * (height / 3)) + (line_width/1) + 4;
        const int y2 = ((col + 1) * (height / 3)) - (line_width/1) - 4;
        const int state = m_tictactoe.GetSquare(row,col);
        if (state == TicTacToe::player1)
        {
          //player1 = cross
          painter.drawLine(x1,y1,x2,y2);
          painter.drawLine(x1,y2,x2,y1);
        }
        else if (state == TicTacToe::player2)
        {
          //player1 = circle
          painter.drawEllipse(x1,y1,x2-x1,y2-y1);
        }
      }
    }
  }

  private:
  TicTacToe m_tictactoe;
  int GetWidth() const { return 300.0; }
  int GetHeight() const { return 300.0; }

  void OnClicked(const Wt::WMouseEvent& e)
  {
    if (m_tictactoe.GetWinner() != TicTacToe::no_winner) return;
    const int x = 3 * e.widget().x / this->GetWidth();
    if (x < 0 || x > 2) return;
    const int y = 3 * e.widget().y / this->GetHeight();
    if (y < 0 || y > 2) return;
    if (m_tictactoe.CanDoMove(x,y))
    {
      m_tictactoe.DoMove(x,y);
      //emit that the state has changed
      this->m_signal_state_changed();
    }
    if (m_tictactoe.GetWinner() != TicTacToe::no_winner)
    {
      //emit that there is a winner
      this->m_signal_has_winner();
    }
    this->update();
  }
};

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

Wt::WApplication *createApplication(
  const Wt::WEnvironment& env)
{
  return new WtApplication(env);
}

int main(int argc, char **argv)
{
  return WRun(argc, argv, &createApplication);
}

