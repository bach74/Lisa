// =============================================================================
//  CSVPlotExporter.cpp   version:  1.5
//  
//  Copyright (C) 2007-2010 by Bach 
//  This file is part of the LiSA project.
//  The LiSA project is licensed under MIT license.
// 
// =============================================================================

#include "stdafx.h"
#include "CSVPlotExporter.h"
#include "exception.h"


/**-------------------------------------------------------------------------------
	CSVPlotExporter

	@brief
	@return
---------------------------------------------------------------------------------*/
CSVPlotExporter::CSVPlotExporter()
{
	mpFile = NULL;
}

/**-------------------------------------------------------------------------------
	startCSVFile

	@brief open a file, ready for data points to be added
	@param fileSuffix
	@param gnuformat
	@return void
---------------------------------------------------------------------------------*/
void CSVPlotExporter::startCSVFile(const char* fileSuffix, bool gnuformat)
{
	time_t seconds = time(NULL);

	char filename[256];

	if (!gnuformat)
	{
		sprintf(filename, "graphplots / % ld_ % s.csv", seconds, fileSuffix); // work out a filename based on the fileSuffix and the time
	}
	else
	{
		sprintf(filename, "graphplots / % ld_ % s.gnuplot", seconds, fileSuffix); // work out a filename based on the fileSuffix and the time
	}

	mpFile = fopen(filename, "w"); // Open file

	if (!mpFile)
	{
		throw Exception("ERROR: Could not open csv file % s for writing\n", filename);
	}
}

/**-------------------------------------------------------------------------------
	writePlotTitle

	@brief
	@param title
	@param gnuformat
	@return void
---------------------------------------------------------------------------------*/
void CSVPlotExporter::writePlotTitle(const char* title, bool gnuformat)
{
	if (!mpFile)
	{
		throw Exception("ERROR: a csv has not been opened for writing\n","CSVPlotExporter.cpp");
	}

	if (!gnuformat)
	{
		fprintf(mpFile, "\"%s\",\n", title); // print
	}
	else
	{
		fprintf(mpFile, "%s\n", title); // print
	}
}

/**-------------------------------------------------------------------------------
	writeXTitle

	@brief
	@param title
	@param gnuformat
	@return void
---------------------------------------------------------------------------------*/
void CSVPlotExporter::writeXTitle(const char* title, bool gnuformat)
{
	if (!mpFile)
	{
		throw Exception("ERROR: a csv has not been opened for writing","CSVPlotExporter.cpp");
	}

	if (!gnuformat)
	{
		fprintf(mpFile, "\"%s\",", title); // print
	}
	else
	{
		fprintf(mpFile, "%s ", title); // print
	}
}

/**-------------------------------------------------------------------------------
	writeYTitle

	@brief
	@param title
	@param gnuformat
	@return void
---------------------------------------------------------------------------------*/
void CSVPlotExporter::writeYTitle(const char* title, bool gnuformat)
{
	if (!mpFile)
	{
		throw Exception("ERROR: a csv has not been opened for writing","CSVPlotExporter.cpp");
	}

	if (!gnuformat)
	{
		fprintf(mpFile, "\"%s\",\n", title); // print
	}
	else
	{
		fprintf(mpFile, "%s\n", title); // print
	}
}

/**-------------------------------------------------------------------------------
	add2dPoint

	@brief
	@param x
	@param y
	@param gnuformat
	@return void
---------------------------------------------------------------------------------*/
void CSVPlotExporter::add2dPoint(float x, float y, bool gnuformat)
{
	if (!mpFile)
	{
		throw Exception("ERROR: a csv has not been opened for writing","CSVPlotExporter.cpp");
	}

	if (!gnuformat)
	{
		fprintf(mpFile, "%f,%f,\n", x, y); // print
	}
	else
	{
		fprintf(mpFile, "%f %f\n", x, y); // print
	}
}

/**-------------------------------------------------------------------------------
	closeCSVFile

	@brief
	@return bool
---------------------------------------------------------------------------------*/
void CSVPlotExporter::closeCSVFile()
{
	if (!mpFile)
	{
		throw Exception("ERROR: can't close file: a csv has not been opened for writing","CSVPlotExporter.cpp");
	}

	fclose(mpFile); // close file (temp)
	mpFile = NULL;
}
