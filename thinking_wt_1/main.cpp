#include <cstdlib>
#include <sstream>
#include <stdexcept>
#include <string>
#include <Wt/WString>
#include <Wt/WApplication>
#include <Wt/WContainerWidget>
#include <Wt/WPushButton>

///IntToWString converts integer to Wt::WString
///From http://www.richelbilderbeek.nl/CppIntToWString.htm
const Wt::WString IntToWString(const int i)
{
  std::ostringstream s;
  if (!(s << i)) throw std::logic_error("IntToWString failed");
  return Wt::WString(s.str());
}

#include <Wt/WPushButton>

struct WtWidget : public Wt::WPushButton
{
  WtWidget()
    : m_clicks(0)
  {
    setText(IntToWString(m_clicks));
    this->clicked().connect(this,&WtWidget::OnClick);
  }
  private:
  void OnClick()
  {
    ++m_clicks;
    setText(IntToWString(m_clicks));
  }
  int m_clicks;
};

struct WtDialog : public Wt::WContainerWidget
{
  WtDialog()
  : m_widget1(new WtWidget),
    m_widget2(new WtWidget)
  {
    this->addWidget(m_widget1);
    this->addWidget(m_widget2);
  }
  private:
  WtWidget * const m_widget1;
  WtWidget * const m_widget2;
};

struct WtApplication : public Wt::WApplication
{
  WtApplication(const Wt::WEnvironment& env)
    : Wt::WApplication(env),
    m_dialog(new WtDialog)
  {
    this->setTitle("My title");
    root()->addWidget(m_dialog);
  }
  private:
  WtDialog * const m_dialog;
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

