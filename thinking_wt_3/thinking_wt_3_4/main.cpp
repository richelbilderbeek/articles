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
#include <Wt/WText>
#include <Wt/WTextArea>
#include "tictactoe.h"
//---------------------------------------------------------------------------
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
//---------------------------------------------------------------------------
struct WtTicTacToeAboutDialog : public Wt::WContainerWidget
{
  WtTicTacToeAboutDialog()
  : m_button_close(new Wt::WPushButton)
  {
    {
      Wt::WTextArea * text = new Wt::WTextArea;
      text->setText(
        "CppThinkingWt3 (C) 2010 Richel Bilderbeek\n"
        "From http://www.richelbilderbeek.nl/CppThinkingWt3.htm"
        );
      text->setMinimumSize(600,Wt::WLength::Auto);
      this->addWidget(text);
    }
    this->addWidget(new Wt::WBreak);
    this->addWidget(m_button_close);
    m_button_close->setText("Close");
    m_button_close->clicked().connect(
      this,&WtTicTacToeAboutDialog::OnClose);
  }
  boost::signals2::signal<void ()> m_signal_close;
  private:
  Wt::WPushButton * const m_button_close;
  void OnClose()
  {
    //emit that this dialog closes
    m_signal_close();
  }
};
//---------------------------------------------------------------------------
struct WtTicTacToeGameDialog : public Wt::WContainerWidget
{
  WtTicTacToeGameDialog()
  : m_button_close(new Wt::WPushButton),
    m_button_restart(new Wt::WPushButton),
    m_tictactoe(new WtTicTacToeWidget)
  {
    this->addWidget(m_tictactoe);
    this->addWidget(new Wt::WBreak);
    this->addWidget(m_button_restart);
    this->addWidget(m_button_close);
    m_button_close->setText("Close");
    m_button_restart->setText("Restart");
    m_tictactoe->m_signal_state_changed.connect(
      boost::bind(
        &WtTicTacToeGameDialog::OnStateChanged,
        this));
    m_button_close->clicked().connect(
      this,&WtTicTacToeGameDialog::OnClose);
    m_button_restart->clicked().connect(
      this,&WtTicTacToeGameDialog::OnRestart);
  }
  boost::signals2::signal<void ()> m_signal_close;
  private:
  Wt::WPushButton * const m_button_close;
  Wt::WPushButton * const m_button_restart;
  WtTicTacToeWidget * const m_tictactoe;
  void OnClose()
  {
    //emit that this dialog closes
    m_signal_close();
  }
  void OnRestart()
  {
    m_tictactoe->Restart();
  }
  void OnStateChanged()
  {
    switch (m_tictactoe->GetState())
    {
      case TicTacToe::player1:
        m_button_restart->setText("Player 1 has won. Click to restart");
        break;
      case TicTacToe::player2:
        m_button_restart->setText("Player 2 has won. Click to restart");
        break;
      case TicTacToe::draw:
        m_button_restart->setText("Draw. Click to restart");
        break;
      case TicTacToe::no_winner:
        m_button_restart->setText("Restart");
        break;
      default:
        assert(!"Should not get here");
        break;
    }
  }
};
//---------------------------------------------------------------------------
struct WtTicTacToeMenuDialog : public Wt::WContainerWidget
{
  WtTicTacToeMenuDialog()
  : m_button_about(new Wt::WPushButton),
    m_button_start(new Wt::WPushButton)
  {
    this->addWidget(new Wt::WText("TicTacToe"));
    this->addWidget(new Wt::WBreak);
    this->addWidget(m_button_start);
    this->addWidget(new Wt::WBreak);
    this->addWidget(m_button_about);
    m_button_about->setText("About");
    m_button_start->setText("Start");
    m_button_about->clicked().connect(
      this,&WtTicTacToeMenuDialog::OnAbout);
    m_button_start->clicked().connect(
      this,&WtTicTacToeMenuDialog::OnStart);
  }
  boost::signals2::signal<void ()> m_signal_about;
  boost::signals2::signal<void ()> m_signal_start;
  private:
  Wt::WPushButton * const m_button_about;
  Wt::WPushButton * const m_button_start;
  void OnAbout()
  {
    //emit that the about dialog must be opened
    m_signal_about();
  }
  void OnStart()
  {
    //emit that the game must be started
    m_signal_start();
  }
};
//---------------------------------------------------------------------------
struct WtTicTacToeApplication : public Wt::WApplication
{
  WtTicTacToeApplication(const Wt::WEnvironment& env)
    : Wt::WApplication(env)
  {
    this->setTitle("Thinking Wt 3: creating a TicTacToe game");
    ShowMenu();
  }
  private:
  void ShowAbout()
  {
    WtTicTacToeAboutDialog * const d = new WtTicTacToeAboutDialog;
    d->m_signal_close.connect(
    boost::bind(
      &WtTicTacToeApplication::ShowMenu,
      this));
    root()->clear();
    root()->addWidget(d);
  }
  void ShowMenu()
  {
    WtTicTacToeMenuDialog * const d = new WtTicTacToeMenuDialog;
    d->m_signal_about.connect(
    boost::bind(
      &WtTicTacToeApplication::ShowAbout,
      this));
    d->m_signal_start.connect(
    boost::bind(
      &WtTicTacToeApplication::Start,
      this));
    root()->clear();
    root()->addWidget(d);
  }
  void Start()
  {
    WtTicTacToeGameDialog * const d = new WtTicTacToeGameDialog;
    d->m_signal_close.connect(
    boost::bind(
      &WtTicTacToeApplication::ShowMenu,
      this));
    root()->clear();
    root()->addWidget(d);
  }
};
//---------------------------------------------------------------------------
Wt::WApplication *createApplication(
  const Wt::WEnvironment& env)
{
  return new WtTicTacToeApplication(env);
}
//---------------------------------------------------------------------------
int main(int argc, char **argv)
{
  return WRun(argc, argv, &createApplication);
}
//---------------------------------------------------------------------------
