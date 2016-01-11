# anvedi

A data viewer prototype made with Qt and [QCustomPlot](http://qcustomplot.com).

![alt text](https://github.com/ilpropheta/anvedi/blob/master/pics/main-view.png "anvedi")

Replaying some data in Real Time mode:

![alt text](https://github.com/ilpropheta/anvedi/blob/master/pics/real-time.gif "anvedi Real Time")

## In a nutshell

anvedi is a little project I've been shaping to play with [QCustomPlot](http://qcustomplot.com), an excellent Qt library for plotting. Note it's a prototype, this means I allowed myself some design shortcuts and Ive been checking edge cases sparingly.

You can use anvedi both via GUI or via scripting. I usually integrate my Qt projects with QtScript by using another project I developed in 2011: [QShell](https://github.com/ilpropheta/anvedi/tree/master/QShell).

I also ported some QCustomPlot bricks to *QML*, since it's not provided by default. [This part](https://github.com/ilpropheta/anvedi/tree/master/Anvedi/qml-lib) of the repo is devoted to QML porting. More details to be added soon.

Last but not least, anvedi is partially (more tests to be added) tested with QTestLib. Refer to [AnvediCheTests](https://github.com/ilpropheta/anvedi/tree/master/AnvediCheTests) for test cases.

What anvedi does:

* The main purpose of anvedi is plotting data with the same domain (e.g. time series)
* Import/Export of the workspace data (JSON files for simplicity)
* Import/Export of just plot - graphical - information
* Scripting integration
* Per-curve customization
   * Pen color
   * Filtering and hiding
   * Ticks and labels
   * Ranges (min/max)
* Viewer capabilities
   * Customizable background color
   * Rect zoom
   * Vertical cursor
   * Axis auto scaling
* Real Time
   * replay of workspace files
   * really simple acquisition protocol via PIPES
   * interactive Real Time generation by using the console

## Building anvedi

Apart from Qt, anvedi is completely self-contained. [QCustomPlot](http://qcustomplot.com) .h and .cpp (just two files) are added to the project for simplicity.

I have been using Visual Studio 2013 Community Edition. .pro files are provided as well - automatically generated by the Qt Visual Studio add-in.

## Why "anvedi"?

Don't bother to find an acronym of "anvedi". 
This is Roman slang, basically an exclamation of surprise after seeing something impressive, so it roughly means "Look at this!".
