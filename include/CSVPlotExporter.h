#pragma once


/**-------------------------------------------------------------------------------
 little class to export a set of data plots into CSV format for reading into spreadsheets and things
 file is called "TIMESTAMP_PLOTNAME.csv"
 can also be set to save in gnuplot format
---------------------------------------------------------------------------------*/

class CSVPlotExporter
{
	public:
		CSVPlotExporter();
		void startCSVFile(const char* fileSuffix, bool gnuformat = false);
		void writePlotTitle(const char* title, bool gnuformat = false);
		void writeXTitle(const char* title, bool gnuformat = false);
		void writeYTitle(const char* title, bool gnuformat = false);
		void add2dPoint(float x, float y, bool gnuformat = false);
		void closeCSVFile();
	private:
		FILE* mpFile;
};
