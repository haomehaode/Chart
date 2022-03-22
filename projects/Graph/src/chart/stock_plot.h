#ifndef STOCK_PLOT_H
#define STOCK_PLOT_H

#include "plot.h"
#include "graph_global.h"
#include "data.h"
#include <QBarCategoryAxis>
#include <QCandlestickSeries>
#include <QValueAxis>
#include <QCandlestickSet>
#include <QDateTime>
#include <QStack>
#include <QLabel>

class GRAPH_EXPORT StockPlot : public Plot
{

public:

	StockPlot(QWidget* parent = nullptr);

	~StockPlot();

public slots:
	/** �����ʾ */
	virtual void slot_tool_tip(bool status, QCandlestickSet* set);

public:

	void add_stock(QList<CandlestickData>& data_list, const QString& name);

	void delete_stock(const QString& name);

	virtual void init_chart() override;

	virtual void init_axis() override;

	virtual void init_series() override;


private:
	/** ���ݼ��� */
	void prepare_data(QList<CandlestickData>& data_list);

private:
	/** ���ƺ�ϵ��ӳ�� */
	QMap<QString, QCandlestickSeries*> m_name2series;
	/** X �� */
	QBarCategoryAxis* m_axisX = nullptr;
	/** Y �� */
	QValueAxis* m_axisY = nullptr;
	/** ��¼�����᷶Χ */
	QStack<double> m_range[4];
	/** X ��ʱ�� */
	QStringList m_axisx_list;
};

#endif // STOCK_PLOT_H