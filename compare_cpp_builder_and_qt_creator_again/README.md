# Comparison of C++ Builder and Qt Creator again...

This article is the successor of 'Comparison of C++ Builder and Qt
Creator' and is written three
months later, at the 23rd of Agust 2010.

## Quick facts chart

Criterion|C++ Builder 6.0 Enterprise edition|Qt Creator 1.3.1
---|---|---
Owner|Embarcadero Technologies|Qt Development Frameworks
Year of release|2002|2010
Licence|Proprietary|GPL and commercial
Supported operating systems|Windows|Linux, Mac, Windows
How to deploy on other platform|Use emulator on Windows executable|Compile code on other platform
Default supplied compiler| Borland BCC32.EXE version 6.0.10.157|g++ version 4.4.1
Boost compiler support|About 20-60%|100%
Supplied with libraries|CLX, OpenGL, STL, VCL| OpenGL, STL, Qt4
Cpp0x adoption|Already before official standard|Adoption after publication of standard

## Discussion

Below, I discuss the three items I encountered most in detail: writing
console applications, writing GUI applications and documentation needed
to learn both IDEs.

### Console applications

In the previous article, I stated that developing console applications
in both IDE's was easy. But not only does the Qt
Creator support Boost fully (as far
as I know), but an enormous amount of other libraries
as well. This boosts (no pun intended) productivity heavily! I do know
that Embaracadero is working on this, for C++
Builder's successor called for RAD Studio.

What I did not highlight in the previous article, is that C++
Builder and its applications run under Windows only.
Except for platform-specific libraries, I see no
reason to limit oneself to Windows.

### GUI applications

In the previous article, I stated that the GUI designer in C++
Builder was less cluttered with windows. To increase
working space, I learned to set the Widget pane to 'Icon View', so I
could push it to a width of two centimeters. This does not work with the
text-based sidebars on the right. I hope that in a future version, this
sidebar can be hidden by a shortcut-key.

I still believe that it is easier to learn C++
Builder: one can use C++ Builder
without knowing how to design classes. In Qt
Creator one sometimes has implement
sub-classes and override behavior (for example, when one
wants to imlement a clickable QLabel). Although I
believe this design choice of the Qt library is good,
I think it is more difficult for beginners: they will have to struggle
with classes first, before they will understand how to
do this.

What I did not mention earlier about the Qt and C++
Builder architectures, is that the Qt architecture is
const-correct, unlike C++ Builder. This aspect makes
it easier to understand Qt: a const method promises not to modify its
members. In C++ Builder, this is not promised at all.

QLabel is a QWidget to display both text and images.
Why this is not seperated in two widgets remains unknown to me. And I
discovered that QLabel does not emit a signal when it
is clicked. If QLabel would only display text, I would
agree with this design choice: a clickable label can be mimicked by a
flat QButton. But I do wished that an image would emit a signal when
clicked: I use many images as flashy buttons. Personally, I would
suggest two solutions to the problem:

  * 1. let QLabel emit a signal when clicked, or
  * 2. add a QImage widget that emits a signal when clicked

Adding a custom method to a dialog is still tedious in Qt
Creator, but one gets used to it:

  * 1. add the declaration of the slot to the dialog's declaration, for
    example 'private slots: void OnButtonClick();'
  * 2. in the dialog constructor, connect a signal to this slot, for
    example
    'QObject::connect(ui-&gt;button,SIGNAL(clicked()),this,SLOT(OnButtonClick()));'
  * 3. write down the method definition, for example
    'void Dialog::OnButtonClick() { /\* your code \*/ }'

In C++ Builder, this was done within three (really!)
clicks: click on 'Events' of the Object Inspector, then double-click on
the signal you want to respond to.

For the layout managent of the visual components, I have learned to
appreciate the work that all QLayouts do: for simple layouts they do a
great job. But when I want to add certain constraints, this still too
often results in unexpected behaviour: for example, I once had an
application of which I could resize the window to a bigger size, but it
could not be resized to a smaller surface. So, I still think that the
C++ Builder TPanels were more intuitive to use.

It hadn't occurred to me before, to note that Qt
Creator does not have any non-visual QWidgets. Sure,
if a widget is visual by definition, this is logical. But C++
Builder supplied non-visual TComponents, that could be
placed on the window (but never be seen). This has two advantages:

  * 1. it is easier, quicker and safer to manipulate widgets at design
    time. For example, for the C++ Builder TTimer, one can
    set the time, if it already runs, and which method gets called
    after timeout. From then on, the TTimer gets created and deleted by C++
    Builder. In Qt Creator, one have to
    write a QTimer declaration, set its timeout, set if its started, connect
    it to a method, and delete it, each by one line of code
  * 2. a beginner can find the functionality needed and experiment with it.
    I find it hard to imagine how a beginner would discover to use a QTimer.
    In C++ Builder, everybody will discover TTimer within
    the first hours

### Documentation

I have learned that the Qt documentation is very good. Note the word
'learned': the Qt documentation has a learning curve, due to:

  * 1. when searching the documentation about a topic like '2D graphics',
    there are multiple ways
    (QPainter,QGraphicsView,QLabel), some ways using
    classes that are connected to (for a beginner: too) many
    classes, for example when trying to use QGraphicsView,
    QGraphicsScene and QGraphicsItem
  * 2. if you do know the names, and/or do not understand to override
    virtual functions, for example 'paintEvent', it is unclear how to use
    some widgets. For example, if you want to use a QPainter, the
    documentation states: 'The common use of QPainter is inside a widget's
    paint event'. Although the documentation subsequently shows how to
    override the method 'paintEvent', I thought that 'paintEvent' was 'just
    a name'

So, if you understand the documentation of Qt, its content is as good as
C++ Builder's.

Still, there are two thingss:

  * 1. Because C++ Builder is easier to learn (as I
    stated above), I nearly ever needed to use its documentation for VCL
    classes
  * 2. Unlike the Qt documentation, C++ Builder also
    documents STL classes

Summarizing this:

  * 1. The Qt Creator documentation documents its Qt
    classes as well as C++ Builder
    documents its VCL classes
  * 2. The Qt Creator documentation takes time to
    understand, the C++ Builder documentation is more
    intuitive
  * 3. Unlike C++ Builder, the Qt Creator documentation lacks STL classes
    documentation

## Summary

Criterion|C++ Builder 6.0 Enterprise edition|Qt Creator 1.3.1
---|---|---
Development of console applications|Similar, low Boost support|Similar, complete Boost support
GUI designer|Plenty of screen space, all windows can be hidden in the same way, all windows have a shortcut key|Screen cluttered with windows, different ways to hide and show most windows
Initial main|Non-minimal, can be removed ruthlessly|Non-minimal, can be removed ruthlessly
Ease of learning graphical library used by GUI designer|VCL has non-visual components (for example, TTimer) that a beginner can use without writing code|Qt does not have non-visual widgets, so a QTimer's behavior must be written in code, which is harder and error-prone
Component/widget architecture|TLabel for labels, TImage for images|QLabel for both labels and images
Adding methods to dialogs|Easy and transparent|Tedious and less transparent
Component/widget use/re-use and extension|Basic by default, but also possible to reimplement virtual member functions|Reimplementation of virtual member functions with magic names and unknown meaning
Layout management|All Component have an  Alignment property, use of TPanel as workhorses, TPanel works intuitively for complex custom behavior| Layout managers with good default behavior, but less intuitive for more complex custom behavior
Documentation|VCL well documented, easy to read the documentation, STL fully documented|Qt classes well documented, it takes time to learn reading the documentation, no STL documentation

My personal conclusion has remained the same:

  * 1. C++ Builder is easier to learn
  * 2. the extra effort learning Qt Creator is worth
    it, because Qt Creator is cross-platform and has a
    superior compiler

## References

 * 1. [Nokia overview of all Qt classes](http://doc.qt.nokia.com/4.6/classes.html)
 * 2. [The original HTML version](http://richelbilderbeek.nl/CppCompareCppBuilderAndQtCreatorAgain.htm)