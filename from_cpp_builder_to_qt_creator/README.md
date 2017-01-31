# Porting an application from C++ Builder to Qt Creator

This article describes how to port a
C++ Builder (6.0) application to Qt
Creator. The main advantage of doing so, is that the
Windows-only application becomes cross-platform.

This article uses the architecture described in the
article 'Thinking Qt 1: general'

## Overview

This article follows these steps:

1.  Discussing the starting point
2.  Put all Ascii-arter functionality in a class called
    AsciiArter
3.  Put the GUI logic in a platform-independent
    class called
    TestAsciiArterDialog
4.  Put the Qt GUI functionality in a
    class called
    QtTestAsciiArterDialog

## Starting point

This article's starting point is the code from AsciiArter source code version 1.0.

Taking a look at the code, the following improvements can be made:

-   Put all Ascii-arter functionality in a class called
    AsciiArter
-   Put the GUI logic in a platform-independent
    class called
    TestAsciiArterDialog
-   Put the Qt GUI functionality in a
    class called
    QtTestAsciiArterDialog

This change in architecture can be displayed graphically:

Before:

![C++ Builder architecture (png)](CppFromCppBuilderToQtCreatorBefore.png)

Here, all functionality resides in one Winnebago class.

![Qt Creator architecture (png)](CppFromCppBuilderToQtCreator.png)

Here, all functionality is distributed over multiple classes,
keeping open the possibility to transform it into a Wt
web applications (in dashed lines)

## Put all Ascii-arter functionality in a class called AsciiArter

I did the following things:

-   Removed the use of the Windows-only
    TImage class, replaced it by
    requesting a Y-X ordered 2D std::vector of
    greyscales
-   Put all global functions in the
    AsciiArter class
    namespace
-   Added versioning

### asciiarter.h

```
#ifndef ASCIIARTER_H
#define ASCIIARTER_H
//---------------------------------------------------------------------------
#include <string>
#include <vector>
#include <boost/tuple/tuple.hpp>
//---------------------------------------------------------------------------
struct AsciiArter
{
  typedef std::vector<int> Pixel;
  const std::vector<std::string> ImageToAscii(
    const std::vector<std::vector<double> >& image,
    const int width) const;

  static const std::string GetVersion();
  static const std::vector<std::string> GetVersionHistory();

  private:
  static const std::vector<char> m_gradient;
  static const std::vector<char> GetAsciiArtGradient();

  static double GetGreyness(
    const std::vector<std::vector<double> >& image,
    const int x,
    const int y);

  static double GetGreyness(
    const std::vector<std::vector<double> >& image,
    const int x1,
    const int x2,
    const int y);

  static double GetGreyness(
    const std::vector<std::vector<double> >& image,
    const int x1,
    const int y1,
    const int x2,
    const int y2);

  static double GetFractionGrey(
    const std::vector<std::vector<double> >& image,
    const int x1,
    const int y1,
    const int x2,
    const int y2);
};
//---------------------------------------------------------------------------
#endif // ASCIIARTER_H
```

### asciiarter.cpp

```
#include <algorithm>
#include <cassert>
#include <iostream>
#include <numeric>
#include <boost/scoped_ptr.hpp>
#include <boost/numeric/conversion/cast.hpp>
#include "asciiarter.h"
//---------------------------------------------------------------------------
const std::vector<char> AsciiArter::m_gradient
  = AsciiArter::GetAsciiArtGradient();
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppGetAsciiArtGradient.htm
const std::vector<char> AsciiArter::GetAsciiArtGradient()
{
  std::vector<char> chars;
  chars.push_back('M');
  chars.push_back('N');
  chars.push_back('m');
  chars.push_back('d');
  chars.push_back('h');
  chars.push_back('y');
  chars.push_back('s');
  chars.push_back('o');
  chars.push_back('+');
  chars.push_back('/');
  chars.push_back(':');
  chars.push_back('-');
  chars.push_back('.');
  chars.push_back('`');
  chars.push_back(' ');
  return chars;
}
//---------------------------------------------------------------------------
double AsciiArter::GetGreyness(
  const std::vector<std::vector<double> >& image,
  const int x,
  const int y)
{
  assert(!image.empty()
    && "Image is NULL");
  assert(x >= 0
    && "x coordinat is below zero");
  assert(y >= 0
    && "y coordinat is below zero");
  assert(y < boost::numeric_cast<int>(image.size())
    && "y coordinat is beyond image height");
  assert(x < boost::numeric_cast<int>(image[y].size())
    && "x coordinat is beyond image width");
  const double greyness = image[y][x];
  assert(greyness >= 0.0);
  assert(greyness <= 1.0);
  return greyness;
}
//---------------------------------------------------------------------------
//Get a line of pixel's average greyness
double AsciiArter::GetGreyness(
  const std::vector<std::vector<double> >& image,
  const int x1,
  const int x2,
  const int y)
{
  assert(!image.empty()
    && "Image is NULL");
  assert(x1 >= 0
    && "x1 coordinat is below zero");
  assert(x2 >= 0
    && "x2 coordinat is below zero");
  assert(y >= 0
    && "y coordinat is below zero");
  assert(y < boost::numeric_cast<int>(image.size())
    && "y coordinat is beyond image height");
  assert(x1 < x2
    && "X-coordinats must be different and ordered");
  assert(x1 < boost::numeric_cast<int>(image[y].size())
    && "x1 coordinat is beyond image width");
  assert(x2 < boost::numeric_cast<int>(image[y].size())
    && "x2 coordinat is beyond image width");
  assert(image[y].begin() + x2 != image[y].end()
    && "x2 coordinat iterator must not be beyond image width");
  const double average_greyness = std::accumulate(
    image[y].begin() + x1,
    image[y].begin() + x2,
    0.0) / boost::numeric_cast<double>(x2-x1);
  assert(average_greyness >= 0.0);
  assert(average_greyness <= 1.0);
  return average_greyness;
}
//---------------------------------------------------------------------------
//Get a square of pixels' average greyness
double AsciiArter::GetGreyness(
  const std::vector<std::vector<double> >& image,
  const int x1,
  const int y1,
  const int x2,
  const int y2)
{
  assert(y1 < y2
    && "Y-coordinats must be ordered");

  double sum = 0.0;

  for (int y=y1; y!=y2; ++y)
  {
    const double grey = GetGreyness(image,x1,x2,y);
    assert(grey >= 0 && grey < 1.0);
    sum+=grey;
  }
  const double average_greyness = sum
    / boost::numeric_cast<double>(y2 - y1);

  assert(average_greyness >=0.0 && average_greyness <= 1.0);
  return average_greyness;
}
//---------------------------------------------------------------------------
//Generalizes a pixel, line or rectangle to one average greyness
double AsciiArter::GetFractionGrey(
  const std::vector<std::vector<double> >& image,
  const int x1,
  const int y1,
  const int x2,
  const int y2)
{
  assert(x1 <= x2);
  assert(y1 <= y2);
  if (x1 == x2 && y1 == y2) return GetGreyness(image,x1,y1);
  if (y1 == y2) return GetGreyness(image,x1,x2,y1);
  if (x1 == x2)
  {
    assert(y1 < y2);
    double sum = 0;
    for (int y=y1; y!=y2; ++y)
    {
      const double g = GetGreyness(image,x1,y);
      assert(g >= 0.0);
      assert(g <= 1.0);
      sum+=g;
    }
    const double average_greyness
      = sum / boost::numeric_cast<double>(y2-y1);
    assert(average_greyness >= 0.0);
    assert(average_greyness <= 1.0);
    return average_greyness;
  }
  return GetGreyness(image,x1,y1,x2,y2);
}
//---------------------------------------------------------------------------
const std::string AsciiArter::GetVersion()
{
  return "1.0";
}
//---------------------------------------------------------------------------
const std::vector<std::string> AsciiArter::GetVersionHistory()
{
  std::vector<std::string> v;
  v.push_back("2011-03-23: Version 1.0: initial version");
  return v;
}
//---------------------------------------------------------------------------
//'image' must be a y-x-ordered std::vector of grey values
//ranging from [0.0,1.0], where 0.0 denotes black and
//1.0 denotes white.
//From http://www.richelbilderbeek.nl/CppImageToAscii.htm
const std::vector<std::string> AsciiArter::ImageToAscii(
  const std::vector<std::vector<double> >& image,
  const int width) const //How many chars the ASCII image will be wide
{
  //If the number of chars is below 5,
  //the calculation would be more complicated due to a too trivial value of charWidth
  assert(width >= 5);


  //Maxy is in proportion with the bitmap
  const int image_width  = image[0].size();
  const int image_height = image.size();

  const int maxy =
    (static_cast<double>(width)
    / static_cast<double>(image_width))
    * static_cast<double>(image_height);
  assert(maxy > 0);
  const double dX = static_cast<double>(image_width)
    / static_cast<double>(width);
  const double dY = static_cast<double>(image_height)
    / static_cast<double>(maxy);
  assert(dX > 0.0);
  assert(dY > 0.0);

  std::vector<std::string> v;

  for (int y=0; y!=maxy; ++y)
  {
    std::string s;
    for (int x=0; x!=width; ++x)
    {
      const int x1 = std::min(
        static_cast<double>(x) * dX,
        image_width  - 1.0) + 0.5;
      const int y1 = std::min(
        static_cast<double>(y) * dY,
        image_height - 1.0) + 0.5;
      const int x2 = std::min(
        (static_cast<double>(x) * dX) + dX,
        image_width  - 1.0) + 0.5;
      const int y2 = std::min(
        (static_cast<double>(y) * dY) + dY,
        image_height - 1.0) + 0.5;
      assert(x1 >= 0);
      assert(x2 >= 0);
      assert(y1 >= 0);
      assert(y2 >= 0);
      assert(x1 < image_width);
      assert(x2 < image_width);
      assert(y1 < image_height);
      assert(y2 < image_height);

      const double f = GetFractionGrey(image,x1,y1,x2,y2);
      assert(f >= 0.0 && f <= 1.0);
      const int i
        = boost::numeric_cast<int>(
          f * boost::numeric_cast<double>(m_gradient.size() - 1));
      assert(i >= 0);
      assert(i < boost::numeric_cast<int>(m_gradient.size()));
      const char c = m_gradient[i];
      s+=c;
    }
    v.push_back(s);
  }
  return v;
}
//---------------------------------------------------------------------------
```

## Put the GUI logic in a platform-independent class called TestAsciiArterDialog

I did the following things:

-   Removed the use of the Windows-only
    TImage class, replaced it by
    requesting a Y-X ordered 2D std::vector of
    greyscales
-   Added versioning

### testasciiarterdialog.h

```

#ifndef TESTASCIIARTERDIALOG_H
#define TESTASCIIARTERDIALOG_H
//---------------------------------------------------------------------------
#include <string>
#include <vector>
//---------------------------------------------------------------------------
#include <boost/scoped_ptr.hpp>
//---------------------------------------------------------------------------
#include "about.h"
struct AsciiArter;
//---------------------------------------------------------------------------
struct TestAsciiArterDialog
{
  TestAsciiArterDialog();
  const std::vector<std::string>& GetAsciiArt() const { return m_asciiart; }
  bool CanConvert() const;
  void Convert();

  static const About GetAbout();
  static const std::string GetVersion();
  static const std::vector<std::string> GetVersionHistory();

  void SetImage(const std::vector<std::vector<double> >& image);
  void SetWidth(const int width);

  private:
  std::vector<std::string> m_asciiart;
  std::vector<std::vector<double> > m_image;
  int m_width;

  const boost::scoped_ptr<AsciiArter> m_asciiarter;
};
//---------------------------------------------------------------------------
#endif // TESTASCIIARTERDIALOG_H
```

### testasciiarterdialog.cpp

```
#include "asciiarter.h"
#include "testasciiarterdialog.h"
//---------------------------------------------------------------------------
TestAsciiArterDialog::TestAsciiArterDialog()
  : m_width(0),
    m_asciiarter(new AsciiArter)
{

}
//---------------------------------------------------------------------------
bool TestAsciiArterDialog::CanConvert() const
{
  return !m_image.empty() && m_width > 5;
}
//---------------------------------------------------------------------------
void TestAsciiArterDialog::Convert()
{
  m_asciiart = m_asciiarter->ImageToAscii(m_image,m_width);
}
//---------------------------------------------------------------------------
const About TestAsciiArterDialog::GetAbout()
{
  About a(
    "Richel Bilderbeek",
    "TestAsciiArter",
    "tool to test the AsciiArter class",
    "the 23rd of March 2011",
    "2006-2011",
    "http://www.richelbilderbeek.nl/ToolTestAsciiArter.htm",
    GetVersion(),
    GetVersionHistory());
  a.AddLibrary("AsciiArter version: " + AsciiArter::GetVersion());
  return a;
}
//---------------------------------------------------------------------------
const std::string TestAsciiArterDialog::GetVersion()
{
  return "4.0";
}
//---------------------------------------------------------------------------
const std::vector<std::string> TestAsciiArterDialog::GetVersionHistory()
{
  std::vector<std::string> v;
  v.push_back("2006-12-13: Version 1.0: initial version (then called 'AsciiArter') programmed in C++ Builder");
  v.push_back("2006-12-16: Version 2.0: minor improvements");
  v.push_back("2008-06-21: Version 3.0: minor improvements");
  v.push_back("2011-03-23: Version 4.0: port to Qt Creator");
  return v;
}
//---------------------------------------------------------------------------
void TestAsciiArterDialog::SetImage(const std::vector<std::vector<double> >& image)
{
  m_image = image;
}
//---------------------------------------------------------------------------
void TestAsciiArterDialog::SetWidth(const int width)
{
  assert(width > 5);
  m_width = width;
}
//---------------------------------------------------------------------------

```



## Put the Qt GUI functionality in a class called QtTestAsciiArterDialog

I did the following things:

-   Let GUI library used, Qt in this case, convert the QImage to the
    requested Y-X ordered 2D std::vector of greyscales

### qttestasciiarterdialog.h

```
#ifndef QTTESTASCIIARTERDIALOG_H
#define QTTESTASCIIARTERDIALOG_H
//---------------------------------------------------------------------------
#include <QDialog>
//---------------------------------------------------------------------------
#include <boost/scoped_ptr.hpp>
//---------------------------------------------------------------------------
#include "testasciiarterdialog.h"
//---------------------------------------------------------------------------
namespace Ui {
  class QtTestAsciiArterDialog;
}
//---------------------------------------------------------------------------
struct QImage;
//---------------------------------------------------------------------------
class QtTestAsciiArterDialog : public QDialog
{
  Q_OBJECT

public:
  explicit QtTestAsciiArterDialog(QWidget *parent = 0);
  ~QtTestAsciiArterDialog();

protected:
  void changeEvent(QEvent *e);

private:
  Ui::QtTestAsciiArterDialog *ui;
  const boost::scoped_ptr<TestAsciiArterDialog> m_dialog;
  void DrawAsciiArt();

  static const std::vector<std::vector<double> >
    ConvertToGreyYx(const QImage * const i);

private slots:
  void on_button_about_clicked();
  void on_edit_width_textChanged(QString );
  void on_button_load_clicked();
};
//---------------------------------------------------------------------------
#endif // QTTESTASCIIARTERDIALOG_H

```

### qttestasciiarterdialog.cpp

```
#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/numeric/conversion/cast.hpp>
//---------------------------------------------------------------------------
#include <QFileDialog>
#include <QImage>
#include <QPixmap>
//---------------------------------------------------------------------------
#include "asciiarter.h"
#include "testasciiarterdialog.h"
#include "qtaboutdialog.h"
#include "qttestasciiarterdialog.h"
#include "ui_qttestasciiarterdialog.h"
//---------------------------------------------------------------------------
QtTestAsciiArterDialog::QtTestAsciiArterDialog(QWidget *parent)
  : QDialog(parent, Qt::Window),
    ui(new Ui::QtTestAsciiArterDialog),
    m_dialog(new TestAsciiArterDialog)
{
  ui->setupUi(this);
  ui->edit_width->setText("80");
  on_edit_width_textChanged("80");
}
//---------------------------------------------------------------------------
QtTestAsciiArterDialog::~QtTestAsciiArterDialog()
{
  delete ui;
}
//---------------------------------------------------------------------------
void QtTestAsciiArterDialog::changeEvent(QEvent *e)
{
  QDialog::changeEvent(e);
  switch (e->type()) {
  case QEvent::LanguageChange:
    ui->retranslateUi(this);
    break;
  default:
    break;
  }
}
//---------------------------------------------------------------------------
void QtTestAsciiArterDialog::DrawAsciiArt()
{
  if (!m_dialog->CanConvert()) return;

  m_dialog->Convert();

  const std::vector<std::string>& v = m_dialog->GetAsciiArt();
  ui->text->clear();

  BOOST_FOREACH(const std::string& s,v)
  {
    ui->text->appendPlainText(s.c_str());
  }
}
//---------------------------------------------------------------------------
void QtTestAsciiArterDialog::on_button_load_clicked()
{
  QFileDialog d;
  const QString filename = d.getOpenFileName();

  if (!QFile::exists(filename))
  {
    return;
  }

  QImage p(filename);
  const std::vector<std::vector<double> > v
    = ConvertToGreyYx(&p);

  m_dialog->SetImage(v);
  DrawAsciiArt();
}
//---------------------------------------------------------------------------
//Returns a Y-X-ordered std::vector of greynesses.
const std::vector<std::vector<double> >
  QtTestAsciiArterDialog::ConvertToGreyYx(const QImage * const i)
{
  const int maxy = i->height();
  const int maxx = i->width();
  const int n_bytes = i->bytesPerLine() / maxx;

  std::vector<std::vector<double> > v;
  for (int y=0; y!=maxy; ++y)
  {
    v.push_back(std::vector<double>());
    const unsigned char * const line = i->scanLine(y);
    for (int x=0; x!=maxx; ++x)
    {
      int sum = 0;
      for (int byte=0; byte!=n_bytes; ++byte)
      {
        sum += line[(x * n_bytes) + byte];
      }
      const double greyness
        = (boost::numeric_cast<double>(sum)
        / boost::numeric_cast<double>(n_bytes))
        / 256.0;
      assert(greyness >= 0.0);
      assert(greyness <= 1.0);
      v.back().push_back(greyness);

    }
  }
  return v;
}
//---------------------------------------------------------------------------
void QtTestAsciiArterDialog::on_edit_width_textChanged(QString q)
{
  const std::string s = q.toStdString();
  try
  {
    boost::lexical_cast<int>(s);
  }
  catch (boost::bad_lexical_cast&)
  {
    return;
  }
  const int width = boost::lexical_cast<int>(s);
  if (width <= 5) return;
  this->m_dialog->SetWidth(width);
  DrawAsciiArt();

}
//---------------------------------------------------------------------------
void QtTestAsciiArterDialog::on_button_about_clicked()
{
  About a = TestAsciiArterDialog::GetAbout();
  QtAboutDialog d(a);
  d.exec();
}
//---------------------------------------------------------------------------
```

## Conclusion

Instead of explaining all steps in detail, this
article shows a change in architecture from
Windows-only GUI-dependent to platform-independent as described in the
article 'Thinking Qt 1: general'.
These changes can be viewed in in image:

![Before](from_cpp_builder_to_qt_creator_1.png)

![After](from_cpp_builder_to_qt_creator_2.png)
 
 
## External links

 * [The original HTML article](http://richelbilderbeek.nl/CppFromCppBuilderToQtCreator.htm)