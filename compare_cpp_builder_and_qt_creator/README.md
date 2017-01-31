# Comparison of C++ Builder and Qt Creator

This article is about comparing C++ Builder and Qt Creator. After nine
years experience with C++ Builder and working with Qt
Creator for about a year, it is time to make a
personal comparison.

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

For console applications, the switch from C++ Builder
to Qt Creator is easy, as there are few differences
between the IDEs. The main advantage of Qt
Creator is its superior compiler
with 100% (can this be true?) Boost support.

When a console application is started, both C++
Builder and Qt Creator show a
non-minimal `main` function. In both IDEs,
this initial code can be ruthlessly removed.

### GUI applications

For GUI applications, the switch from C++
Builder to Qt Creator is hard. C++
Builder uses the VCL
library, where Qt Creator uses the
very different Qt4 libary.

I have been using the GUI designer on a 1024x768
resolution for Qt Creator and 800x600 for C++
Builder. Although the screen resolution I used for C++
Builder was lower, the screen felt less full: in C++
Builder you can hide all windows by clicking the X on
top-right of eacht window. In Qt Creator some, but
not all, windows can be hidden by clicking on different positions, so it
is easier to clean up the designer screen in C++
Builder.

Personally, the main difference between these graphical libraries is the
ease of self-learning: there are about 800 Qt
classes [1] and about 1000 VCL
classes (estimation from VCL hierarchy
chart). For me, it felt easier to discover the VCL
classes' working: all visual components can be explored
with the Object Inspector and there is a one-to-one transition to do the
same adaptations in code. In my humble opinion, VCL
classes are easier to learn by experimenting with them.

Both C++ Builder and Qt Creator
come with some default visual components/widgets (a C++
Builder Component equals a Qt
Creator Widget). What I do not understand of Qt
Creator (yet), is that one needs a `QLabel` to display
an image, where in C++ Builder one can use a `TLabel`
for text and `TImage` for images. I would find it
appropriate that a QLabel/TLabel displays text only.

A GUI designer does not only enable a programmer to design
a dialog, but also to add member functions to
it. In C++ Builder this is done very transparently: in
the Object Inspector one can select each Component's Events and by
double-clicking generate a custom-named member
function. In Qt Creator one
must implement virtual member
functions with pre-defined names that are not
known to the beginning programmer.

The layout managent of the visual components for me was easier in C++
Builder, where one needs to use TPanels as workhorses
and set their alignments. The layout managers of Qt
Creator work fine, but I have not lost my preferences
for the C++ Builder way.

The architecture of using VCL or Qt
classes differs. Using a VCL
class is basic by default: one
instanciates it and let it be managed by itself or
something else using its interface only. In
Qt classes it is often the case that a
virtual member function needs
to be implemented. For a beginning programmer, these member
function names are nearly magical ('How could I
know that method's name?') as well as their working ('How can I know
what a paintEvent does?'). In VCL classes,
member functions can be redefined as well, but
need not to by default. So in my humble opinion, I think that for a
beginning programmer the Qt classes appear
less straightforward.

### Documentation

For both C++ Builder and Qt
Creator one needs books or online documentation to
find the way. All the Qt classes' methods, properties, ancestors and
derived classes can all be found online, where the VCL classes this is
not the case: these are found in the context-sensitive help of C++
Builder where these are described briefly. Unexpectly,
when I started working with C++ Builder, I did not
need this high-detail information, as I could find out how it worked
myself. When I need to get something done with Qt, I find myself having
my (two) Qt books opened and about eight Firefox tabs open, often
without finding the answer to my question. So I would say that Qt
Creator is well-documented but not in a way that a
beginner needs, where with C++ Builder the brief
documentation suffices.

## Summary


Criterion|C++ Builder 6.0 Enterprise edition|Qt Creator 1.3.1
---|---|---
Development of console applications|Similar, low Boost support|Similar, complete Boost support
GUI designer|Plenty of screen space, all windows can be hidden in the same way, all windows have a shortcut key|Screen cluttered with windows, different ways to hide and show most windows
Ease of learning graphical library used by GUI designer|VCL has one-to-one transition from GUI design and code|Qt has slight differences between GUI design and code
Component/widget architecture|TLabel for labels, TImage for images|QLabel for both labels and images
Adding methods to dialogs|Transparent, by double-clicking an Event in the Object Inspector, possible to redefine member function names|Less transparent, by redefining virtual member functions, with names unknown to beginner programmer
Component/widget use/re-use and extension|Basic by default, but also possible to reimplement virtual member functions|Reimplementation of virtual member functions with magic names and unknown meaning
Layout management|All Component have an Alignment property, use of TPanel as workhorses|Layout managers
Documentation|Brief and sufficient|Extensive, but not suited for beginners' needs

My personal conclusion is that I have found it easier to learn to use
C++ Builder than Qt Creator. Qt
Creator is still young and will hopefully make my
critique redundant in the future. That Qt Creator is
free, cross-platform and is supplied with a great
compiler makes the transition from C++
Builder to Qt Creator worth it. I
hope my website will help others to take the same step.

## Post your feedback

Feel free to post your feedback about this article at the Issues of this GitHub

## [References](CppReferences.htm)

 * 1. [Nokia overview of all Qt classes](http://doc.qt.nokia.com/4.6/classes.html)
 * 2. [The original HTML article](http://richelbilderbeek.nl/CppCompareCppBuilderAndQtCreator.htm)


