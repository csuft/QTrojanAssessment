#ifndef REALTIMEDEMO_H
#define REALTIMEDEMO_H

#include <QDialog>
#include <QDateTime>
#include <QTimer>
#include <QLabel>
#include "3rdParty/ChartDirector/qchartviewer.h"

// The number of samples per data series used in this demo
const int sampleSize = 240;

class RealtimeChart : public QWidget {
    Q_OBJECT
public:
    RealtimeChart(const char* ytitle, const char* mainTitle, const char* labela, const char* labelb, QWidget *parent = 0);

private:
    double m_timeStamps[sampleSize];	// The timestamps for the data series
    double m_dataSeriesA[sampleSize];	// The values for the data series A
    double m_dataSeriesB[sampleSize];	// The values for the data series B
    double m_dataSeriesC[sampleSize];	// The values for the data series C

    QDateTime m_nextDataTime;           // Used by the random number generator to generate realtime data.

    QChartViewer *m_ChartViewer;        // QChartViewer control
    QTimer *m_ChartUpdateTimer;         // The chart update timer

	const char* m_yTitle;
	const char* m_mainTitle;
	const char* m_labelA;
	const char* m_labelB;

private slots:
    void getData();                     // Get new data values
    void updateChart();                 // Update the chart.
    void drawChart();                   // Draw the chart.
};

#endif // REALTIMEDEMO_H
