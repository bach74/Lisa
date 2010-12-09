#pragma once

#include "LabelWidget.h"
#include "CSVPlotExporter.h"

// This is a widget that will draw a line graph onto the screen inside a semi-transparent panel

#define MAXGRAPHDATAPOINTS 1000000
#define GRAPHLINESMAX 10

// a data point along a line (linked list based)
struct LineDataPoint
{
	bool deleteNextPoints();
	LineDataPoint* next; // next point (or NULL)
	LineDataPoint* prev; // next point (or NULL)
	float x; // real x value (only floats at this stage are supported)
	float y; // real y value (only floats at this stage are supported)
};

// representation of a line on the graph (collection of variables associated with each line)
struct GraphLine
{
	Ogre::ManualObject* mpLineObject;
	Ogre::SceneNode* mpLineNode;
	Ogre::MaterialPtr mpLineMaterial;
	LineDataPoint* mpLatestDataPoint; // linked list of data points
	LineDataPoint* mpEarliestDataPoint;
	char mLineName[256]; // name of this data plot
	int mCurrentDataPoints;
	int mMaximumDataPoints; // max nodes to store in memory (to prevent mem leak)
};


/**-------------------------------------------------------------------------------
    LineGraphWidget

    @brief A widget for line graphs - does static and dynamic (real-time scrolling monitor) graphs
    @return
---------------------------------------------------------------------------------*/
class LineGraphWidget
{
	public:
		// general widget stuff
		LineGraphWidget(const char* uniqueName, float parentTop, float parentLeft, float parentBottom,
			float parentRight, float xProp, float yProp, float width, float height, Ogre::SceneManager* sceneManager);
		~LineGraphWidget();

		// change size of widget, and to some extent squish the sub-window to fit in this new size
		void setWidgetSize(float xpixels, float ypixels);

		// tell this widget what the parent's dimensions are. Needs to be called if parent moved.
		void defineParentBounds(float top, float left, float bottom, float right);

		 // show widget on screen
		void show();

		 // hide widget from view
		void hide();

		  // move to a position relative to size of parent (0.0-1.0)
		void moveWidget(float xProp, float yProp);

		// specialized widget stuff
		void freeLines(); // free all lines from graph
		void setGraphTitle(const char* title); // set the title text for the graph
		void setXAxisTitle(const char* title); // set title for x axis
		void setYAxisTitle(const char* title); // set title for y axis
		void setXAxisMax(float xAxisMax); // set axis scale
		void setXAxisMin(float xAxisMin); // set axis scale
		void setYAxisAutoScale(bool autoscale){mYAxisPegged=!autoscale;}
		void setKeepBoxAspectRation(bool val) { mKeepBoxAspectRation = val; }
		void setShowAxes(bool val);

		// indicate the the x-axis should keep this scale but scroll for new values (like a CPU monitor)
		void setXAxisScroll(bool scroll = true) { mXAxisScrolling = scroll; }
		void setXAxisInterval(float interval) { mXInterval = interval; }

		void setYAxisMax(float yAxisMax); // set axis scale
		void setYAxisMin(float yAxisMin); // set axis scale
		int createLine(float r = 1.0f, float g = 1.0f, float b = 1.0f); // create a new line with this colour
		void addPointToLine(int lineIndex, float realXValue, float realYValue, bool respectXIntervals = false, bool optimisePoints = false); // add a new data point to a line
		void removeAllPointsFromLine(int lineIndex, bool isAxisLineIndex = false); // delete a line's points

		void savePlotToFile(int lineIndex, bool gnuformat = false); // save to file (to both csv and gnuplot formats)

	private:

		void initAxisLines();
		void freeAxisLines();
		float getXAxisProportion(float realXValue); // return real value in terms of 0-1 place along the axis
		float getYAxisProportion(float realYValue); // return real value in terms of 0-1 place along the axis
		float getAdjustedScreenXProportion(float graphXProp); // given a proportion of graph width, return this as identity-matrix adjusted full screen proportion
		float getAdjustedScreenYProportion(float graphYProp); // given a proportion of graph width, return this as identity-matrix adjusted full screen proportion
		void redrawLine(int lineIndex, bool isAxisLineIndex = false); // redraw the line whenever it changes

		Ogre::SceneManager* mSceneManager;
		Ogre::Overlay* mOverlay; // overlay panel for drawing background and holding widget bits (except lines)
		Ogre::OverlayElement* mBaseElement; // base overlay element
		Ogre::OverlayContainer* mContainer; // container for parts of overlay
		Ogre::BorderPanelOverlayElement* mBorderPanel; // graphical border around widget

		CSVPlotExporter mCSVExporter; // an exporter for saving to csv files
		GraphLine mGraphLine[GRAPHLINESMAX]; // lines to draw on graph (note: index -1 is x-axis and -2 is y-axis)
		GraphLine mAxisLine[2]; // axis lines

		LabelWidget* mGraphTitleLabel; // main title of the graph
		LabelWidget* mXAxisLabel; // title of x-axis
		LabelWidget* mXAxisMaxLabel; // eg "100.00 ms^-1"
		LabelWidget* mXAxisMinLabel; // eg "0.00 ms^-1"
		LabelWidget* mYAxisLabel; // title of x-axis
		LabelWidget* mYAxisMaxLabel;
		LabelWidget* mYAxisMinLabel;

		char mUniqueName[256];
		float mParentBoundTop; // bound of parent window (i.e. main viewport)
		float mParentBoundLeft; // bound of parent window (i.e. main viewport)
		float mParentBoundBottom; // bound of parent window (i.e. main viewport)
		float mParentBoundRight; // bound of parent window (i.e. main viewport)

		float mWidgetWidthPixels; // in pixels
		float mWidgetHeightPixels; // in pixels
		float mXProp; // position relative to parent
		float mYProp; // position relative to parent
		float mXPos; // position in pixels (absolute)
		float mYPos; // position in pixels (absolute)
		float mGraphingAreaWidth; // sub-window bound of widget that is used for drawing lines
		float mGraphingAreaHeight; // sub-window bound of widget that is used for drawing lines
		float mGraphingAreaLeftMargin; // sub-window bound of widget that is used for drawing lines
		float mGraphingAreaTopMargin; // sub-window bound of widget that is used for drawing lines

		float mXAxisMax; // scale of x axis
		float mXAxisMin; // scale of x axis
		float mYAxisMax; // scale of y axis
		float mYAxisMin; // scale of y axis
		float mXInterval; // frequency to record each data point

		int mNumLinesForGraph; // number of lines being drawn on graph
		bool mXAxisScrolling; // if graph scrolls along x-axis
		bool mXAxisPegged; // if graph can auto scale or not
		bool mYAxisPegged; // if graph can auto scale or not
		bool mKeepBoxAspectRation; // keep box aspect ratio
		bool mHiding; // if overlay is hidden
		bool mUseInterval;
		
		bool mShowAxisLines;
};

