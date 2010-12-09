#include "stdafx.h"
#include "LineGraphWidget.h"
#include "exception.h"

#define FONT_SIZE  11
#define FONT_FACE "Tahoma"

/**-------------------------------------------------------------------------------
    deleteNextPoints

    @brief auto-delete the whole line point by point
    @return void
---------------------------------------------------------------------------------*/
bool LineDataPoint::deleteNextPoints()
{
	if (next == NULL)
	{
		// send signal that we are the last point left and can be deleted
		return true;
	}

	if (next->deleteNextPoints())   // tell next point to delete all after it
	{
		delete next; // delete the last point
		next = NULL; // set it back to null
	}

	return false;
}

/**-------------------------------------------------------------------------------
    LineGraphWidget

    @brief
    @param uniqueName
    @param parentTop
    @param parentLeft
    @param parentBottom
    @param parentRight
    @param xProp
    @param yProp
    @param width
    @param height
    @param sceneManager
    @return
---------------------------------------------------------------------------------*/
LineGraphWidget::LineGraphWidget(const char* uniqueName, float parentTop, float parentLeft, float parentBottom,
                                 float parentRight, float xProp, float yProp, float width, float height, Ogre::SceneManager* sceneManager)
{
	if (!sceneManager)   // validate params
	{
		throw Exception("ERROR: scene manager passed is not valid", "lineGraphwidget");
	}

	mSceneManager = sceneManager;

	mParentBoundTop = parentTop;
	mParentBoundLeft = parentLeft;
	mParentBoundBottom = parentBottom;
	mParentBoundRight = parentRight;
	mXProp = xProp;
	mYProp = yProp;
	strcpy(mUniqueName, uniqueName);
	mHiding = false;

	mWidgetWidthPixels = width;
	mWidgetHeightPixels = height;
	mGraphingAreaWidth = mWidgetWidthPixels * 0.8f;
	mGraphingAreaHeight = mWidgetHeightPixels * 0.8f;
	mGraphingAreaLeftMargin = mWidgetWidthPixels * 0.1f;
	mGraphingAreaTopMargin = mWidgetHeightPixels * 0.1f;

	mXAxisMax = 100.0f;
	mXAxisMin = 0.0f;
	mYAxisMax = 100.0f;
	mYAxisMin = 0.0f;
	mXInterval = 0.0f;

	mNumLinesForGraph = 0;

	mXAxisScrolling = false;
	mXAxisPegged = false; // autoscale set to true by default
	mYAxisPegged = false; // autoscale set to true by default

	mKeepBoxAspectRation = false;

	// initialise the overlay for the menu
	char tmp[256];
	sprintf(tmp, "%s_overlay", uniqueName);
	mOverlay = Ogre::OverlayManager::getSingleton().create(tmp);

	if (!mOverlay)
	{
		throw Exception("ERROR: Could not create LineGraphWidget overlay", "lineGraphwidget");
	}

	mOverlay->setZOrder(600);  // set render order (0-650 are valid)

	// create a container panel for the widget
	sprintf(tmp, "%s_FB", uniqueName);  // name of the panel
	mBaseElement = Ogre::OverlayManager::getSingleton().createOverlayElement("BorderPanel", tmp);
	mContainer = static_cast<Ogre::OverlayContainer*>(mBaseElement);

	if (!mContainer)
	{
		throw Exception("ERROR: Could not create LineGraphWidget container", "lineGraphwidget");
	}

	// set up the border panel (with another horrible cast)
	mBorderPanel = static_cast<Ogre::BorderPanelOverlayElement*>(mBaseElement);

	mBorderPanel->setMetricsMode(Ogre::GMM_PIXELS);
	mBorderPanel->setBorderSize(0.5f);
	mBorderPanel->setMaterialName("GraphBackground");
	mBorderPanel->setBorderMaterialName("GraphBorder");
	mBorderPanel->setDimensions(mWidgetWidthPixels, mWidgetHeightPixels);
	mOverlay->add2D(mContainer);

	// provide boundaries and move widget into place
	defineParentBounds(mParentBoundTop, mParentBoundLeft, mParentBoundBottom, mParentBoundRight);

	// put a label on the graph
	sprintf(tmp, "%s_graphtitlelabel", uniqueName);
	mGraphTitleLabel = new LabelWidget(mContainer, tmp, mXPos, mYPos, mXPos + mWidgetWidthPixels, mYPos + mWidgetHeightPixels, 0.2f, 0.0f, "Title of this graph");
	mGraphTitleLabel->centreText();
	mGraphTitleLabel->setFont(FONT_FACE);
	mGraphTitleLabel->setSize(FONT_SIZE);
	mGraphTitleLabel->show();
	// x-axis label
	sprintf(tmp, "%s_graphxaxislabel", uniqueName);
	mXAxisLabel = new LabelWidget(mContainer, tmp, mXPos, mYPos, mXPos + mWidgetWidthPixels, mYPos + mWidgetHeightPixels, 0.5f, 0.90f, "Time (s)");
	mXAxisLabel->centreText();
	mXAxisLabel->setFont(FONT_FACE);
	mXAxisLabel->setSize(FONT_SIZE);
	mXAxisLabel->show();
	// y-axis label
	sprintf(tmp, "%s_graphyaxislabel", uniqueName);
	mYAxisLabel = new LabelWidget(mContainer, tmp, mXPos, mYPos, mXPos + mWidgetWidthPixels, mYPos + mWidgetHeightPixels, 0.04f, 0.5f, "Y");
	mYAxisLabel->centreText();
	mYAxisLabel->setFont(FONT_FACE);
	mYAxisLabel->setSize(FONT_SIZE);
	mYAxisLabel->show();

	float leftXProp = mGraphingAreaLeftMargin / mWidgetWidthPixels; // x prop of the y axis (left of x axis)
	float rightXProp = mGraphingAreaWidth / mWidgetWidthPixels + leftXProp;
	float topYProp = mGraphingAreaTopMargin / mWidgetHeightPixels; // top y prop of y axis
	float bottomYProp = mGraphingAreaHeight / mWidgetHeightPixels + topYProp;

	// x-axis max value label
	sprintf(tmp, "%s_graphxaxismaxvaluelabel", uniqueName);
	mXAxisMaxLabel = new LabelWidget(mContainer, tmp, mXPos, mYPos, mXPos + mWidgetWidthPixels, mYPos + mWidgetHeightPixels, rightXProp, 0.9f, "units");
	mXAxisMaxLabel->setFont(FONT_FACE);
	mXAxisMaxLabel->setSize(FONT_SIZE);
	mXAxisMaxLabel->show();
	// x-axis min value label
	sprintf(tmp, "%s_graphxaxisminvaluelabel", uniqueName);
	mXAxisMinLabel = new LabelWidget(mContainer, tmp, mXPos, mYPos, mXPos + mWidgetWidthPixels, mYPos + mWidgetHeightPixels, leftXProp, 0.9f, "units");
	mXAxisMinLabel->setFont(FONT_FACE);
	mXAxisMinLabel->setSize(FONT_SIZE);
	mXAxisMinLabel->show();
	// y-axis max value label
	sprintf(tmp, "%s_graphyaxismaxvaluelabel", uniqueName);
	mYAxisMaxLabel = new LabelWidget(mContainer, tmp, mXPos, mYPos, mXPos + mWidgetWidthPixels, mYPos + mWidgetHeightPixels, 0.0125f, topYProp, "units");
	mYAxisMaxLabel->setFont(FONT_FACE);
	mYAxisMaxLabel->setSize(FONT_SIZE);
	mYAxisMaxLabel->show();
	// y-axis min value label
	sprintf(tmp, "%s_graphyaxisminvaluelabel", uniqueName);
	mYAxisMinLabel = new LabelWidget(mContainer, tmp, mXPos, mYPos, mXPos + mWidgetWidthPixels, mYPos + mWidgetHeightPixels, 0.0125f, bottomYProp, "units");
	mYAxisMinLabel->setFont(FONT_FACE);
	mYAxisMinLabel->setSize(FONT_SIZE);
	mYAxisMinLabel->show();

	// create axis lines
	mShowAxisLines = true;
	initAxisLines();
}

/**-------------------------------------------------------------------------------
    free

    @brief free the whole widget
    @param sceneManager
    @return void
---------------------------------------------------------------------------------*/
LineGraphWidget::~LineGraphWidget()
{
	hide();
	freeAxisLines();
	freeLines();

	delete mYAxisMinLabel;
	mYAxisMinLabel = NULL;
	delete mYAxisMaxLabel;
	mYAxisMaxLabel = NULL;
	delete mXAxisMinLabel;
	mXAxisMinLabel = NULL;
	delete mXAxisMaxLabel;
	mXAxisMaxLabel = NULL;
	delete mXAxisLabel;
	mXAxisLabel = NULL;
	delete mYAxisLabel;
	mYAxisMaxLabel = NULL;
	delete mGraphTitleLabel;
	mGraphTitleLabel = NULL;
	Ogre::OverlayManager::getSingleton().destroyOverlayElement(mBaseElement);
	Ogre::OverlayManager::getSingleton().destroy(mOverlay);
	mBaseElement = NULL;
	mContainer = NULL;
	mBorderPanel = NULL;
	mOverlay = NULL;

}

/**-------------------------------------------------------------------------------
    setWidgetSize

    @brief Change size of widget, and to some extent squish the sub-window to fit in this new size
    @param xpixels
    @param ypixels
    @return void
---------------------------------------------------------------------------------*/
void LineGraphWidget::setWidgetSize(float xpixels, float ypixels)
{
	float graphAreaWidthProp = mGraphingAreaWidth / mWidgetWidthPixels;
	float graphAreaHeightProp = mGraphingAreaHeight / mWidgetHeightPixels;
	mWidgetWidthPixels = xpixels;
	mWidgetHeightPixels = ypixels;
	mGraphingAreaWidth = graphAreaWidthProp * mWidgetWidthPixels;
	mGraphingAreaHeight = graphAreaHeightProp * mWidgetHeightPixels;
}


/**-------------------------------------------------------------------------------
    defineParentBounds

    @brief Define boundaries (in pixels) of the widget that this one is nested in (so that proportions work properly)
    @param top
    @param left
    @param bottom
    @param right
    @return void
---------------------------------------------------------------------------------*/
void LineGraphWidget::defineParentBounds(float top, float left, float bottom, float right)
{
	mParentBoundTop = top;
	mParentBoundLeft = left;
	mParentBoundBottom = bottom;
	mParentBoundRight = right;

	if (!mBaseElement)
	{
		throw Exception("ERROR: No file LineGraphWidget base element allocated", "lineGraphwidget");
	}

	moveWidget(mXProp, mYProp);
}

/**-------------------------------------------------------------------------------
    moveWidget

    @brief
    @param xProp
    @param yProp
    @return void
---------------------------------------------------------------------------------*/
void LineGraphWidget::moveWidget(float xProp, float yProp)
{
	mXProp = xProp;
	mYProp = yProp;

	if (!mBaseElement)
	{
		throw Exception("ERROR: No file LineGraphWidget element allocated", "lineGraphwidget");
		// no memory allocated
	}

	// set position - can't just change metrics mode because all the size attributes are in pixels
	mXPos = mParentBoundLeft + (mParentBoundRight - mParentBoundLeft) * xProp;  // get screen-proportionate position
	mYPos = mParentBoundTop + (mParentBoundBottom - mParentBoundTop) * yProp;   // get screen-proportionate position
	mBorderPanel->setLeft(mXPos);
	mBorderPanel->setTop(mYPos);
}


/**-------------------------------------------------------------------------------
    show

    @brief Show the widget
    @return void
---------------------------------------------------------------------------------*/
void LineGraphWidget::show()
{
	if (!mOverlay)
	{
		throw Exception("ERROR: No LineGraphWidget Panel in memory to show", "lineGraphwidget");
	}

	mHiding = false;
	mOverlay->show();

	// show the lines
	for (int i = 0; i < mNumLinesForGraph; i++)
	{
		redrawLine(i);
	}

	if (mShowAxisLines) {
		// show axis
		for (int i = 0; i < 2; i++)
		{
			redrawLine(i, true);
		}
	}

}

/**-------------------------------------------------------------------------------
    hide

    @brief Hide the widget
    @return void
---------------------------------------------------------------------------------*/
void LineGraphWidget::hide()
{
	if (!mOverlay)
	{
		throw Exception("ERROR: No LineGraphWidget in memory to hide", "lineGraphwidget");
	}

	mHiding = true;
	mOverlay->hide();

	// hide the lines
	for (int i = 0; i < mNumLinesForGraph; i++)
	{
		mGraphLine[i].mpLineObject->clear();
	}

	// hide axis
	if (mShowAxisLines) {
		for (int i = 0; i < 2; i++)
		{
			mAxisLine[i].mpLineObject->clear();
		}
	}
}


/**-------------------------------------------------------------------------------
    freeLines

    @brief Remove all the lines from the graph and free memory
    @return void
---------------------------------------------------------------------------------*/
void LineGraphWidget::freeLines()
{
	for (int i = 0; i < mNumLinesForGraph; i++)
	{
		// remove all the data points and clean memory
		removeAllPointsFromLine(i);

		mGraphLine[i].mMaximumDataPoints = MAXGRAPHDATAPOINTS; // reset data allowance
		mGraphLine[i].mCurrentDataPoints = 0; // reset point count
		strcpy(mGraphLine[i].mLineName, ""); // reset name
		char tmp[256]; // handle holder
		sprintf(tmp, "%sLineMaterial%i", mUniqueName, i); // get material name
		Ogre::MaterialManager::getSingleton().remove(tmp); // remove material

		if (!mGraphLine[i].mpLineNode)
		{
			throw Exception("ERROR: line node i not found to destroy", "lineGraphWidget");
		}

		mSceneManager->destroySceneNode(mGraphLine[i].mpLineNode);
		mGraphLine[i].mpLineNode = NULL;
		mSceneManager->destroyManualObject(mGraphLine[i].mpLineObject); // remove object
	}

	mNumLinesForGraph = 0;
}


/**-------------------------------------------------------------------------------
    setGraphTitle

    @brief Set the title text for the graph
    @param title
    @return void
---------------------------------------------------------------------------------*/
void LineGraphWidget::setGraphTitle(const char* title)
{
	mGraphTitleLabel->setText(title);
	mGraphTitleLabel->centreText();
}

/**-------------------------------------------------------------------------------
    setXAxisTitle

    @brief Set the title text for the x axis
    @param title
    @return void
---------------------------------------------------------------------------------*/
void LineGraphWidget::setXAxisTitle(const char* title)
{
	mXAxisLabel->setText(title);
	mXAxisLabel->centreText();
}

/**-------------------------------------------------------------------------------
    setYAxisTitle

    @brief Set the title text for the y axis
    @param title
    @return void
---------------------------------------------------------------------------------*/
void LineGraphWidget::setYAxisTitle(const char* title)
{
	mYAxisLabel->setText(title);
	mYAxisLabel->centreText();
}

/**-------------------------------------------------------------------------------
    setXAxisMax

    @brief Set scale of axis
    @param xAxisMax
    @return void
---------------------------------------------------------------------------------*/
void LineGraphWidget::setXAxisMax(float xAxisMax)
{
	mXAxisMax = xAxisMax; // update actual value used for extent
	char tmp[256];
	sprintf(tmp, "%.2f", mXAxisMax);
	mXAxisMaxLabel->setText(tmp); // change value    displayed on axis label
}


/**-------------------------------------------------------------------------------
    setXAxisMin

    @brief Set scale of axis
    @param xAxisMin
    @return void
---------------------------------------------------------------------------------*/
void LineGraphWidget::setXAxisMin(float xAxisMin)
{
	mXAxisMin = xAxisMin;
	char tmp[256];
	sprintf(tmp, "%.2f", mXAxisMin);
	mXAxisMinLabel->setText(tmp); // change value    displayed on axis label
}


/**-------------------------------------------------------------------------------
    setYAxisMax

    @brief Set scale of axis
    @param yAxisMax
    @return void
---------------------------------------------------------------------------------*/
void LineGraphWidget::setYAxisMax(float yAxisMax)
{
	mYAxisMax = yAxisMax;
	char tmp[256];
	sprintf(tmp, "%.2f", mYAxisMax);
	mYAxisMaxLabel->setText(tmp); // change value    displayed on axis label
}


/**-------------------------------------------------------------------------------
    setYAxisMin

    @brief Set scale of axis
    @param yAxisMin
    @return void
---------------------------------------------------------------------------------*/
void LineGraphWidget::setYAxisMin(float yAxisMin)
{
	mYAxisMin = yAxisMin;
	char tmp[256];
	sprintf(tmp, "%.2f", mYAxisMin);
	mYAxisMinLabel->setText(tmp); // change value    displayed on axis label
}


/**-------------------------------------------------------------------------------
    createLine

    @brief Add a new line to the graph with this colour
    @param r
    @param g
    @param b
    @return int
---------------------------------------------------------------------------------*/
int LineGraphWidget::createLine(float r, float g, float b)
{

	if (mNumLinesForGraph >= GRAPHLINESMAX)   // validate params
	{
		throw Exception("ERROR: maximum graph lines exceeded, can not create new line.", "lineGraphwidget");
	}

	int ourLine = mNumLinesForGraph; // get line number
	mNumLinesForGraph++; // incr number of lines used

	// start actual line construction
	char tmp[256];
	sprintf(tmp, "%sLineObject%i", mUniqueName, ourLine); // name line
	mGraphLine[ourLine].mpLineObject = mSceneManager->createManualObject(tmp); // create line's manual object

	// Use identity view/projection matrices (presumably this means draw to screen coordinates rather than world coords)
	mGraphLine[ourLine].mpLineObject->setUseIdentityProjection(true);
	mGraphLine[ourLine].mpLineObject->setUseIdentityView(true);

	sprintf(tmp, "%sLineNode%i", mUniqueName, ourLine);
	mGraphLine[ourLine].mpLineNode = mSceneManager->getRootSceneNode()->createChildSceneNode(tmp);
	sprintf(tmp, "%sLineMaterial%i", mUniqueName, ourLine);
	mGraphLine[ourLine].mpLineMaterial = Ogre::MaterialManager::getSingleton().create(tmp, OGRE_DEBUG_GROUP);
	mGraphLine[ourLine].mpLineMaterial->setReceiveShadows(false);
	mGraphLine[ourLine].mpLineMaterial->getTechnique(0)->setLightingEnabled(true);

	// create colour for line (white only at this stage)
	mGraphLine[ourLine].mpLineMaterial->getTechnique(0)->getPass(0)->setDiffuse(r, g, b, 0);
	mGraphLine[ourLine].mpLineMaterial->getTechnique(0)->getPass(0)->setAmbient(r, g, b);
	mGraphLine[ourLine].mpLineMaterial->getTechnique(0)->getPass(0)->setSelfIllumination(r, g, b);

	mGraphLine[ourLine].mpLineNode->attachObject(mGraphLine[ourLine].mpLineObject);
	mGraphLine[ourLine].mpLineObject ->setRenderQueueGroup(Ogre::RENDER_QUEUE_OVERLAY + 1); // render just after overlays

	mGraphLine[ourLine].mpLatestDataPoint = NULL; // set points list to none
	mGraphLine[ourLine].mpEarliestDataPoint = NULL;
	strcpy(mGraphLine[ourLine].mLineName, "unnamed data set");
	mGraphLine[ourLine].mCurrentDataPoints = 0;
	mGraphLine[ourLine].mMaximumDataPoints = MAXGRAPHDATAPOINTS; // 100 thousand line max points?

	return ourLine; // return index of this line
}


/**-------------------------------------------------------------------------------
    addPointToLine

    @brief Add a new data point to a line
    @param lineIndex
    @param realXValue
    @param realYValue
    @param respectXIntervals
    @param optimisePoints
    @return void
---------------------------------------------------------------------------------*/
void LineGraphWidget::addPointToLine(int lineIndex, float realXValue, float realYValue, bool respectXIntervals, bool optimisePoints)
{
	if ((lineIndex < 0) || (lineIndex >= mNumLinesForGraph))   // validate
	{
		throw Exception("ERROR: That line is not in the graph", "lineGraphwidget");
	}

	// make sure line hasn't got more than maximum allowed data points allocated on it
	if (mGraphLine[lineIndex].mCurrentDataPoints >= mGraphLine[lineIndex].mMaximumDataPoints)
	{
		std::stringstream buf;
		buf << "WARNING: too many points (" << mGraphLine[lineIndex].mCurrentDataPoints << ") added to line#" << lineIndex;
		throw Exception(buf.str(), "lineGraphWidget");
	}

	LineDataPoint* currentPoint = mGraphLine[lineIndex].mpLatestDataPoint; // get end of list
	LineDataPoint* previousPoint = NULL;

	// only collect data at set x point (or near to)
	if (respectXIntervals)
	{
		if (mXInterval == 0.0f)
		{
			throw Exception("ERROR: LineGraphWidget::addPointToLine with respect intervals on; will not work as you have not setXinterval()", "lineGraphwidget");
		}

		unsigned long  upcomingInterval = 0;

		if (currentPoint != NULL)
		{
			unsigned long adjustedValue = (unsigned long)(realXValue  * 1000000.0f);
			unsigned long adjustedInterval = (unsigned long)(mXInterval  * 1000000.0f);
			unsigned long adjustedCurrentX = (unsigned long)(currentPoint->x * 1000000.0f);
			upcomingInterval = adjustedCurrentX + adjustedInterval;

			if (adjustedValue < upcomingInterval)
			{
				// don't need this point, ignore
			}

			while (adjustedValue > upcomingInterval + adjustedInterval)   // make sure we didn't skip an interval
			{
				upcomingInterval = upcomingInterval + adjustedInterval;
			}
		}

		// stick the measurement to the data point
		realXValue = (float)(upcomingInterval) / 1000000.0f;
		// NOTE - can collect x-axis error at this point as well if desired
	}

	previousPoint = currentPoint; // keep track of end of list
	currentPoint = new LineDataPoint; // make new list item

	if (!currentPoint)   // validate new memory
	{
		throw Exception("ERROR: mem overflow creating new data plot point", "lineGraphwidget");
	}

	currentPoint->x = realXValue; // set data
	currentPoint->y = realYValue; // set data
	currentPoint->prev = previousPoint; // point to previous end of list
	currentPoint->next = NULL;

	if (previousPoint != NULL)
	{
		previousPoint->next = currentPoint;
	}
	else
	{
		mGraphLine[lineIndex].mpEarliestDataPoint = currentPoint;
	}

	mGraphLine[lineIndex].mpLatestDataPoint = currentPoint; // tell line about this new end point
	mGraphLine[lineIndex].mCurrentDataPoints++;

	// check if data y values are 3-in-row or more and can wipe intermediate values for space (good for scrolling display, not for graphing results with error bars)
	if (optimisePoints)
	{
		if (previousPoint != NULL)
		{
			if (previousPoint->prev != NULL)
			{
				float firstPoint = previousPoint->prev->y;
				int truncated = (int)(firstPoint * 100.0f); // reduce accuracy of instruments to 2 d.p
				firstPoint = (float)truncated / 100.0f; // reduce accuracy of instruments to 2 d.p
				float secondPoint = previousPoint->y; // reduce accuracy of instruments to 2 d.p
				truncated = (int)(secondPoint * 100.0f); // reduce accuracy of instruments to 2 d.p
				secondPoint = (float)truncated / 100.0f; // reduce accuracy of instruments to 2 d.p
				float thirdPoint = realYValue; // reduce accuracy of instruments to 2 d.p
				truncated = (int)(thirdPoint * 100.0f); // reduce accuracy of instruments to 2 d.p
				thirdPoint = (float)truncated / 100.0f; // reduce accuracy of instruments to 2 d.p

				if ((firstPoint == secondPoint) && (firstPoint == thirdPoint))
				{
					currentPoint->prev = previousPoint->prev; // cut out 'second' point
					delete previousPoint;
					previousPoint = currentPoint->prev; // change this as well just in case we want it later

					if (previousPoint != NULL)
					{
						previousPoint->next = currentPoint;
					}

					mGraphLine[lineIndex].mCurrentDataPoints--;
				}
			}
		}
	}

	// check if need to adjust graph scale (if this point is outside current graph bounds)
	bool rescaled = false;

	if (realXValue < mXAxisMin)
	{
		if (!mXAxisPegged)   // expand graph
		{
			setXAxisMin(realXValue);
			rescaled = true;
		}
	}

	if (realXValue > mXAxisMax)
	{
		if (mXAxisScrolling)
		{
			float axisRange = mXAxisMax - mXAxisMin;
			setXAxisMax(realXValue);
			setXAxisMin(mXAxisMax - axisRange);
			rescaled = true;
		}
		else if (!mXAxisPegged)
		{
			setXAxisMax(realXValue); // auto-scale the graph
			rescaled = true;
		}
	}

	if (realYValue < mYAxisMin)
	{
		if (!mYAxisPegged)
		{
			setYAxisMin(realYValue);
			rescaled = true;
		}
	}

	if (realYValue > mYAxisMax)
	{
		if (!mYAxisPegged)
		{
			setYAxisMax(realYValue);
			rescaled = true;
		}
	}

	if (!mHiding)
	{
		if (rescaled)
		{
			if (mKeepBoxAspectRation)
			{
				// keep aspects so box looks like a box on screen
				float aspectGraph = (mXAxisMax - mXAxisMin) / (mYAxisMax - mYAxisMin);
				float aspectWidget = mWidgetWidthPixels / mWidgetHeightPixels;
				float correction = fabs(aspectWidget / aspectGraph);

				if (correction < 1)
				{
					// correct y-axis
					float a = (mYAxisMax + mYAxisMin) / 2;
					float b = fabs(mYAxisMax - mYAxisMin) * 1 / correction / 2;
					setYAxisMax(a + b);
					setYAxisMin(a - b);
				}
				else
				{
					// correct x-axis
					float a = (mXAxisMax + mXAxisMin) / 2;
					float b = fabs(mXAxisMax - mXAxisMin) * correction / 2;
					setXAxisMax(a + b);
					setXAxisMin(a - b);
				}
			}

			// redraw all lines on graph to new scale
			for (int i = 0; i < mNumLinesForGraph; i++)
			{
				redrawLine(i);
			}
		}
		else
		{
			// just redraw our line
			redrawLine(lineIndex);
		}
	}
}


/**-------------------------------------------------------------------------------
    removeAllPointsFromLine

    @brief Delete a line's points (freeing memory)
    @param lineIndex
    @param isAxisLineIndex
    @return void
---------------------------------------------------------------------------------*/
void LineGraphWidget::removeAllPointsFromLine(int lineIndex, bool isAxisLineIndex)
{
	if (!isAxisLineIndex)
	{
		if ((lineIndex < 0) || (lineIndex >= mNumLinesForGraph))   // validate
		{
			throw Exception("ERROR: That line is not in the graph", "lineGraphwidget");
		}
	}
	else
	{
		if ((lineIndex < 0) || (lineIndex >= 2))   // validate
		{
			throw Exception("ERROR: That line is not in the graph", "lineGraphwidget");
		}
	}

	LineDataPoint* currentPoint = NULL;

	if (!isAxisLineIndex)
	{
		currentPoint = mGraphLine[lineIndex].mpLatestDataPoint; // get end of list
	}
	else
	{
		currentPoint = mAxisLine[lineIndex].mpLatestDataPoint; // get end of list
	}

	if (currentPoint != NULL)
	{
		// line was not already empty

		if (!currentPoint->deleteNextPoints())   // auto-delete line point by point
		{
			throw Exception("ERROR: could not delete line - malformed line", "lineGraphwidget");
		}

		delete currentPoint; // delete final point
	}

	if (!isAxisLineIndex)
	{
		mGraphLine[lineIndex].mpLatestDataPoint = NULL; // and set it to NULL
		mGraphLine[lineIndex].mpEarliestDataPoint = NULL;
	}
	else
	{
		mAxisLine[lineIndex].mpLatestDataPoint = NULL; // and set it to NULL
		mAxisLine[lineIndex].mpEarliestDataPoint = NULL;
	}
}


/**-------------------------------------------------------------------------------
    savePlotToFile

    @brief Save to file
    @param lineIndex
    @param gnuformat
    @return void
---------------------------------------------------------------------------------*/
void LineGraphWidget::savePlotToFile(int lineIndex, bool gnuformat)
{
	if ((lineIndex < 0) || (lineIndex >= mNumLinesForGraph))   // validate
	{
		throw Exception("ERROR: That line is not in the graph", "lineGraphwidget");
	}

	// go through a loop of all points
	LineDataPoint* currentPoint = NULL;
	currentPoint = mGraphLine[lineIndex].mpEarliestDataPoint; // get end of list

	if (currentPoint == NULL)
	{
		// line was already empty so return true
	}

	char tmp[256];
	sprintf(tmp, "%s_%i", mUniqueName, lineIndex);

	// open file
	mCSVExporter.startCSVFile(tmp, gnuformat);

	if (!gnuformat)   // write titles and things
	{
		mCSVExporter.writePlotTitle(mGraphTitleLabel->getText(), gnuformat);
		mCSVExporter.writeXTitle(mXAxisLabel->getText(), gnuformat);
		mCSVExporter.writeYTitle(mYAxisLabel->getText(), gnuformat);
	}

	// loop through points printing them
	while (currentPoint != NULL)
	{
		mCSVExporter.add2dPoint(currentPoint->x, currentPoint->y, gnuformat);
		currentPoint = currentPoint->next;
	}

	mCSVExporter.closeCSVFile();
}


/**-------------------------------------------------------------------------------
    initAxisLines

    @brief Set up lines on axis
    @return void
---------------------------------------------------------------------------------*/
void LineGraphWidget::initAxisLines()
{
	// start actual line construction
	char tmp[256];

	for (int i = 0; i < 2; i++)
	{
		sprintf(tmp, "%sAxisLineObject%i", mUniqueName, i); // name line
		mAxisLine[i].mpLineObject = mSceneManager->createManualObject(tmp); // create line's manual object
		// Use identity view/projection matrices (presumably this means draw to screen coordinates rather than world coords)
		mAxisLine[i].mpLineObject->setUseIdentityProjection(true);
		mAxisLine[i].mpLineObject->setUseIdentityView(true);
		sprintf(tmp, "%sAxisLineNode%i", mUniqueName, i);
		mAxisLine[i].mpLineNode = mSceneManager->getRootSceneNode()->createChildSceneNode(tmp); // attach line to scengraph
		sprintf(tmp, "%sAxisLineMaterial%i", mUniqueName, i);
		mAxisLine[i].mpLineMaterial = Ogre::MaterialManager::getSingleton().create(tmp, OGRE_DEBUG_GROUP); // not sure if 'debugger' needs to be unique
		mAxisLine[i].mpLineMaterial->setReceiveShadows(false);
		mAxisLine[i].mpLineMaterial->getTechnique(0)->setLightingEnabled(true);
		// create colour for line (white only at this stage)
		mAxisLine[i].mpLineMaterial->getTechnique(0)->getPass(0)->setDiffuse(1.0f, 1.0f, 1.0f, 0); // white lines
		mAxisLine[i].mpLineMaterial->getTechnique(0)->getPass(0)->setAmbient(1.0f, 1.0f, 1.0f);
		mAxisLine[i].mpLineMaterial->getTechnique(0)->getPass(0)->setSelfIllumination(1.0f, 1.0f, 1.0f);
		mAxisLine[i].mpLineNode->attachObject(mAxisLine[i].mpLineObject);
		mAxisLine[i].mpLineObject ->setRenderQueueGroup(Ogre::RENDER_QUEUE_OVERLAY + 1); // render just after overlays
		mAxisLine[i].mpLatestDataPoint = NULL; // set points list to none
		mAxisLine[i].mpEarliestDataPoint = NULL; // set points list to none
		strcpy(mAxisLine[i].mLineName, "axis_line");
		mAxisLine[i].mCurrentDataPoints = 0;
		mAxisLine[i].mMaximumDataPoints = MAXGRAPHDATAPOINTS; // 100 line max points?

		// create points along line
		LineDataPoint* currentPoint = NULL;
		LineDataPoint* previousPoint = NULL;
		float notchX = 0.0f;
		float notchY = 0.0f;
		float notchInterval = 0.10f; // ten notches (10% of graph each)
		float notchHeight = 0.05f; // 5% of graph height high
		float notchWidth = 0.01f;

		for (int j = 0; j < 11; j++)   // create 10 notches along line
		{
			// first create line at bottom of notch
			previousPoint = currentPoint; // remember existing end point if there is one
			currentPoint = new LineDataPoint; // make new list item
			currentPoint->x = notchX; // set data
			currentPoint->y = notchY; // set data
			currentPoint->prev = previousPoint; // point to previous end of list
			currentPoint->next = NULL;
			mAxisLine[i].mpLatestDataPoint = currentPoint; // tell line about this new end point

			if (mAxisLine[i].mpEarliestDataPoint == NULL)
			{
				mAxisLine[i].mpEarliestDataPoint = currentPoint;
			}

			// second create line at top of notch
			if (i == 0)
			{
				notchY = notchHeight;
			}
			else
			{
				notchX = notchWidth;
			}

			previousPoint = currentPoint; // remember existing end point if there is one
			currentPoint = new LineDataPoint; // make new list item
			currentPoint->x = notchX; // set data
			currentPoint->y = notchY; // set data
			currentPoint->prev = previousPoint; // point to previous end of list
			currentPoint->next = NULL;
			mAxisLine[i].mpLatestDataPoint = currentPoint; // tell line about this new end point
			// third go back to the bottom of the notch
			if (i == 0)
			{
				notchY = 0.0f;
			}
			else
			{
				notchX = 0.0f;
			}

			previousPoint = currentPoint; // remember existing end point if there is one
			currentPoint = new LineDataPoint; // make new list item
			currentPoint->x = notchX; // set data
			currentPoint->y = notchY; // set data
			currentPoint->prev = previousPoint; // point to previous end of list
			currentPoint->next = NULL;
			mAxisLine[i].mpLatestDataPoint = currentPoint; // tell line about this new end point
			// move on to next notch
			if (i == 0)
			{
				notchX = notchX + notchInterval; // go to next notch along
			}
			else
			{
				notchY = notchY + notchInterval;
			}
		}

		redrawLine(i, true);
	}
}

/**-------------------------------------------------------------------------------
    freeAxisLines

    @brief Remove axis lines
    @return void
---------------------------------------------------------------------------------*/
void LineGraphWidget::freeAxisLines()
{
	for (int i = 0; i < 2; i++)
	{
		// remove all the data points and clean memory
		removeAllPointsFromLine(i, true);

		mAxisLine[i].mMaximumDataPoints = MAXGRAPHDATAPOINTS; // reset data allowance
		mAxisLine[i].mCurrentDataPoints = 0; // reset point count
		strcpy(mAxisLine[i].mLineName, ""); // reset name
		char tmp[256]; // handle holder
		sprintf(tmp, "%sAxisLineMaterial%i", mUniqueName, i); // get material name
		Ogre::MaterialManager::getSingleton().remove(tmp); // remove material

		if (mAxisLine[i].mpLineNode)
		{
			mSceneManager->destroySceneNode(mAxisLine[i].mpLineNode);
			mAxisLine[i].mpLineNode = NULL;
			mSceneManager->destroyManualObject(mAxisLine[i].mpLineObject);
		}
	}
}


/**-------------------------------------------------------------------------------
    getXAxisProportion

    @brief Return real value in terms of 0-1 place along the axis
    @param realXValue
    @return float
---------------------------------------------------------------------------------*/
float LineGraphWidget::getXAxisProportion(float realXValue)
{
	// assuming here that realXValue is in valid range already
	float axisRange = mXAxisMax - mXAxisMin;
	return (realXValue - mXAxisMin) / axisRange;
}


/**-------------------------------------------------------------------------------
    getYAxisProportion

    @brief Return real value in terms of 0-1 place along the axis
    @param realYValue
    @return float
---------------------------------------------------------------------------------*/
float LineGraphWidget::getYAxisProportion(float realYValue)
{
	// assuming here that realXValue is in valid range already
	float axisRange = mYAxisMax - mYAxisMin;
	return (realYValue - mYAxisMin) / axisRange;
}


/**-------------------------------------------------------------------------------
    getAdjustedScreenXProportion

    @brief Given a proportion of widget width, return this as identity-matrix adjusted full screen proportion
    @param graphXProp
    @return float
---------------------------------------------------------------------------------*/
float LineGraphWidget::getAdjustedScreenXProportion(float graphXProp)
{
	float graphLeftSide = mXProp * mParentBoundRight + mGraphingAreaLeftMargin; // adjust these to fit in graph sub-area of widget
	float numerator = graphLeftSide + graphXProp * mGraphingAreaWidth; // get x pixels along screen
	float screenProportion = numerator / mParentBoundRight; // assuming mParentBoundRight is SCREEN right
	float identityAdjustedProportion = screenProportion * 2.0f - 1.0f; // put in the -1.0f-1.0f range

	return identityAdjustedProportion;
}


/**-------------------------------------------------------------------------------
    getAdjustedScreenYProportion

    @brief  Given a proportion of widget height, return this as identity-matrix adjusted full screen proportion
            note that in this case the reverse of normal proportions is true so 0.0 is the BOTTOM of the graph
    @param graphYProp
    @return float
---------------------------------------------------------------------------------*/
float LineGraphWidget::getAdjustedScreenYProportion(float graphYProp)
{
	float graphTopSide = mYProp * mParentBoundBottom + mGraphingAreaTopMargin; // adjust these to fit in graph sub-area of widget
	float numerator = graphTopSide + (1.0f - graphYProp) * mGraphingAreaHeight; // get y pixels along screen
	float screenProportion = numerator / mParentBoundBottom; // assuming mParentBoundBottom is SCREEN bottom
	float identityAdjustedProportion = (screenProportion * 2.0f - 1.0f) * -1.0f; // put in the -1.0f-1.0f range

	return identityAdjustedProportion;
}


/**-------------------------------------------------------------------------------
    redrawLine

    @brief Draw a line on the graph using a set of points
    @param lineIndex
    @param isAxisLineIndex
    @return void
---------------------------------------------------------------------------------*/
void LineGraphWidget::redrawLine(int lineIndex, bool isAxisLineIndex)
{
	if (!isAxisLineIndex)
	{
		if ((lineIndex < 0) || (lineIndex >= mNumLinesForGraph))   // validate
		{
			throw Exception("ERROR: That line is not in the graph", "lineGraphwidget");
		}
	}
	else
	{
		if ((lineIndex < 0) || (lineIndex >= 2))   // validate
		{
			throw Exception("ERROR: That line is not in the graph", "lineGraphwidget");
		}
	}

	LineDataPoint* currentPoint = NULL;

	if (!isAxisLineIndex)
	{
		currentPoint = mGraphLine[lineIndex].mpLatestDataPoint; // get the first point
	}
	else
	{
		currentPoint = mAxisLine[lineIndex].mpLatestDataPoint; // get the first point
	}

	char tmp[256]; // name for material

	if (!isAxisLineIndex)
	{
		sprintf(tmp, "%sLineMaterial%i", mUniqueName, lineIndex); // use material that we set up earlier
		mGraphLine[lineIndex].mpLineObject->clear();
	}
	else
	{
		sprintf(tmp, "%sAxisLineMaterial%i", mUniqueName, lineIndex); // use material that we set up earlier
		mAxisLine[lineIndex].mpLineObject->clear();
	}

	// Use infinite AAB to always stay visible
	Ogre::AxisAlignedBox aabInf;
	aabInf.setInfinite();

	if (!isAxisLineIndex)
	{
		mGraphLine[lineIndex].mpLineObject->setBoundingBox(aabInf);
		mGraphLine[lineIndex].mpLineObject->begin(tmp, Ogre::RenderOperation::OT_LINE_STRIP); // signal start of line-draw process
	}
	else
	{
		mAxisLine[lineIndex].mpLineObject->setBoundingBox(aabInf);
		mAxisLine[lineIndex].mpLineObject->begin(tmp, Ogre::RenderOperation::OT_LINE_STRIP); // signal start of line-draw process
	}

	while (currentPoint != NULL)   // draw all points until at end of list
	{
		float xProp = 0.0f;
		float yProp = 0.0f;

		if (!isAxisLineIndex)
		{
			xProp = getXAxisProportion(currentPoint->x); // get x value as 0-1 of current axis scale
			yProp = getYAxisProportion(currentPoint->y); // get y value as 0-1 of current axis scale
		}
		else
		{
			xProp = currentPoint->x; // axis points are already in the form 0-1 of graph width
			yProp = currentPoint->y; // axis points are already in the form 0-1 of graph height
		}

		float screenXPlacement = getAdjustedScreenXProportion(xProp); // get adjusted x pos for point
		float screenYPlacement = getAdjustedScreenYProportion(yProp); // get adjusted y pos for point

		if (!isAxisLineIndex)
		{
			bool doNotDraw = false; // whether or not to draw the point
			//if (mXAxisPegged) { // if graph is not resizing then check if point is outside bounds
			if ((currentPoint->x > mXAxisMax) || (currentPoint->x < mXAxisMin))
			{
				doNotDraw = true;
			}

			//}
			//if (mYAxisPegged) { // if graph is not resizing then check if point is outside bounds
			if ((currentPoint->y > mYAxisMax) || (currentPoint->y < mYAxisMin))
			{
				doNotDraw = true;
			}

			//}
			if (!doNotDraw)   // draw point unless it is outside graph bounds (and graph was not resized)
			{
				mGraphLine[lineIndex].mpLineObject->position(screenXPlacement, screenYPlacement, 0.0f); // add draw point
			}
		}
		else
		{
			mAxisLine[lineIndex].mpLineObject->position(screenXPlacement, screenYPlacement, 0.0f); // add draw point
		}

		currentPoint = currentPoint->prev; // get next point
	}

	if (!isAxisLineIndex)
	{
		mGraphLine[lineIndex].mpLineObject->end(); // signal finish drawing line
	}
	else
	{
		mAxisLine[lineIndex].mpLineObject->end(); // signal finish drawing line
	}
}

/**-------------------------------------------------------------------------------
    setShowAxes

    @brief
    @param val
    @return void
---------------------------------------------------------------------------------*/
void LineGraphWidget::setShowAxes(bool val)
{
	if (mShowAxisLines && !val) {
		freeAxisLines();
		mShowAxisLines=false;
	} else if (!mShowAxisLines && val) {
		initAxisLines();
		mShowAxisLines=true;
	}
}

