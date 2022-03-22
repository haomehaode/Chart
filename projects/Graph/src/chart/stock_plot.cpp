#pragma execution_character_set("utf-8")

#include "stock_plot.h"
#include <QBarCategoryAxis>
#include "tool_tip.h"
#include "chart_view.h"

StockPlot::StockPlot(QWidget *parent)
	: Plot(parent)
{
	init_series();
	init_chart();
	init_axis();
}

StockPlot::~StockPlot()
{
	//QCandlestickSeries���ú�����
	//append(self, set)������setָ���ĵ�����̨��Ŀ��ӵ���̨ͼ�У������������Ȩ���������Ϊ�ջ�����ϵ���У��򲻻ḽ�Ӹ�������ӳɹ�����True�����򷵻�False��
	//clear(self) : ����ɾ��ͼ�е�������Ŀ��
	//remove(self, set)������̨ͼ��ɾ��setָ������Ŀ��
	//take(self, set)����ͼ�л�ȡ��setָ���ĵ�����Ŀ������ɾ������Ŀ��
	//setBodyOutlineVisible(self, bodyOutlineVisible)��������̨�����Ƿ�ɼ���
	//setBodyWidth(self, bodyWidth)��������̨��Ŀ����Կ�ȣ���ΧΪ0.0��1.0��
	//setBrush(self, brush)��������̨��Ŀ�Ļ�ˢ��
	//setPen(self, pen)��������̨��Ŀ�����Ļ��ʡ�
	//setCapsVisible(self, capsVisible)��������̨��Ŀ���Ƿ�ɼ���
	//setCapsWidth(self, capsWidth)�� ������̨��Ŀ�ǵĿ�ȡ�
	//setDecreasingColor(self, decreasingColor)��������̨��Ŀ�ݼ���ɫ��
	//setIncreasingColor(self, increasingColor)��������̨��Ŀ������ɫ��
	//setMaximumColumnWidth(self, maximumColumnWidth)��������̨��Ŀ�������(������Ϊ��λ������Ϊ��ֵ��ʾû������ȡ����и�ֵ����ת��Ϊ - 1.0)��
	//setMinimumColumnWidth(self, minimumColumnWidth)��������̨��Ŀ����С���(������Ϊ��λ������Ϊ��ֵ��ʾû������ȡ����и�ֵ����ת��Ϊ - 1.0)��

	//QCandlestickSeries�����źţ�
	//bodyOutlineVisibilityChanged(self)����̨��Ŀ���������Ŀɼ��Ը���ʱ�����������źš�
	//bodyWidthChanged(self)����̨��Ŀ�Ŀ�ȸ���ʱ�����������źš�
	//brushChanged(self)����̨��Ŀ��ˢ����ʱ�����������źš�
	//candlestickSetsAdded(self, sets)����setsָ������̨��Ŀ��ӵ���̨ͼ��ʱ�����������źš�
	//candlestickSetsRemoved(self, sets)������̨ͼ��ɾ��setsָ������̨��Ŀʱ�����������źš�
	//capsVisibilityChanged(self)����̨��Ŀ�ǵĿɼ����Ը���ʱ�����������źš�
	//capsWidthChanged(self) : ��̨��Ŀ�ǵĿ�ȸ���ʱ�����������źš�
	//clicked(self, set) : ����ͼ������setָ������̨��Ŀʱ�����������źš�
	//countChanged(self)������̨ͼ������̨��Ŀ��������������ʱ�����������źš�
	//decreasingColorChanged(self) : ����̨��Ŀ����ɫ����ʱ�����������źš�
	//doubleClicked(self, set)��˫��ͼ������setָ������̨��Ŀʱ�����������źš�
	//hovered(self, status, set)���������ͣ����ָ������̨��Ŀsetʱ������źű����䡣�������������Ŀ�Ϸ�ʱ��state��ΪTrue����������ٴ��ƿ�ʱ��state��ΪFalse��
	//increasingColorChanged(self)����̨��Ŀ��ɫ����ʱ�����������źš�
	//maximumColumnWidthChanged(self) : ��̨��Ŀ������п����仯ʱ�����������źš�
	//minimumColumnWidthChanged(self)����̨��Ŀ����С�п����仯ʱ�����������źš�
	//penChanged(self)����̨ͼ�Ļ��ʷ�������ʱ�ᷢ�����źš�
	//pressed(self, set)�����û�����setָ������̨��Ŀ����ס��갴ťʱ�����������źš�
	//released(self, set)�����û��ͷ�set��ָ������̨��Ŀ�ϵ����ʱ�����������źš�

	//QCandlestickSet���ú�����
	//setBrush(self, brush)��������Ŀ�Ļ�ˢΪbrush��
	//setPen(self, pen)��������Ŀ�Ļ���Ϊpen��
	//setClose(self, close)��������Ŀ�����̼�Ϊclose��
	//setHigh(self, high)��������Ŀ������ֵΪhigh��
	//setLow(self, low)��������Ŀ������ֵΪlow��
	//setOpen(self, open)��������Ŀ�Ŀ��̼ۡ�
	//setTimestamp(self, timestamp)��������Ŀ��ʱ�����

	//QCandlestickSet�����źţ�
	//brushChanged(self)������ʱ��ˢ�����������źš�
	//penChanged(self)�����Ļ���ʱ�����������źš�
	//clicked(self)��������Ŀʱ�����������źš�
	//doubleClicked(self)��˫����Ŀʱ�����������źš�
	//hovered(self, status)���������ͣ����Ŀ��ʱ�����������źš�
	//pressed(self)�����û�����������ס��갴ťʱ�����������źš�
	//released(self)�����û��ͷŶ���Ŀ���ͷ����ʱ�����������źš�
	//closeChanged(self)����Ŀ���̼۷����ı�ʱ�������źš�
	//highChanged(self)����Ŀ����ֵ����ʱ�����������źš�
	//lowChanged(self)����Ŀ����ֵ����ʱ�����������źš�
	//openChanged(self)����Ŀ���̼۱仯ʱ�������źš�
	//timestampChanged(self)������Ŀʱ�������ʱ�����������źš�
}

void StockPlot::slot_tool_tip(bool status, QCandlestickSet* set)
{
	if (m_tooltip == nullptr)
		m_tooltip = new ToolTip(m_chart,this);
	if (status) {
		m_tooltip->setText(QString("����: %1 \n����: %2\n���: %3\n���: %4 ")
			.arg(set->open()).arg(set->close()).arg(set->high()).arg(set->low()));
		QPointF point = m_chartview->mapFromGlobal(QCursor::pos());
		m_tooltip->setAnchor(point);
		m_tooltip->setZValue(11);
		m_tooltip->updateGeometry();
		m_tooltip->show();
	}
	else
		m_tooltip->hide();
}

void StockPlot::add_stock(QList<CandlestickData>& data_list, const QString& name)
{
	if (m_name2series.contains(name))
		return;

	prepare_data(data_list);

	QCandlestickSeries* series = new QCandlestickSeries();
	series->setName(name);
	series->setIncreasingColor(QColor(Qt::green));
	series->setDecreasingColor(QColor(Qt::red));

	for (auto& item : data_list)
	{
		QCandlestickSet* set = new QCandlestickSet(item.m_timestamp);
		set->setProperty("parent", name);
		set->setOpen(item.m_open);
		set->setHigh(item.m_high);
		set->setLow(item.m_low);
		set->setClose(item.m_close);
		series->append(set);
		m_axisx_list << QDateTime::fromMSecsSinceEpoch(set->timestamp()).toString("dd");
	}

	m_chart->addSeries(series);
	m_name2series[name] = series;
	series->attachAxis(m_axisX);
	series->attachAxis(m_axisY);
	m_axisX->setCategories(m_axisx_list);
	m_axisY->setRange(m_min_y, m_max_y);

	connect(series, &QCandlestickSeries::hovered, this, &StockPlot::slot_tool_tip);
	//connect_markers();
}

void StockPlot::delete_stock(const QString& name)
{
	if (!m_name2series.contains(name))
		return;
	m_chart->removeSeries(m_name2series[name]);
	m_name2series.remove(name);

	m_range[0].pop();
	m_range[1].pop();
	m_range[2].pop();
	m_range[3].pop();

	m_min_x = m_range[0].top();
	m_max_x = m_range[1].top();
	m_min_y = m_range[2].top();
	m_max_y = m_range[3].top();

	m_axisX->setRange(QString::number(m_min_x), QString::number(m_max_x));
	m_axisY->setRange(m_min_y * 0.99, m_max_y * 1.01);
}

void StockPlot::init_chart()
{
	m_chart->legend()->hide();
}

void StockPlot::init_axis()
{
	m_axisX = new QBarCategoryAxis();
	m_chart->addAxis(m_axisX, Qt::AlignBottom);

	m_axisY = new QValueAxis();
	m_chart->addAxis(m_axisY, Qt::AlignLeft);
}

void StockPlot::init_series()
{
	m_name2series.clear();
}

void StockPlot::prepare_data(QList<CandlestickData>& data_list)
{
	for (auto& data : data_list)
	{
		if (data.m_timestamp < m_min_x)
			m_min_x = data.m_timestamp;
		if (data.m_timestamp > m_max_x)
			m_max_x = data.m_timestamp;
		if (data.m_low < m_min_y)
			m_min_y = data.m_low;
		if (data.m_high > m_max_y)
			m_max_y = data.m_high;
	}
	m_range[0].push(m_min_x);
	m_range[1].push(m_max_x);
	m_range[2].push(m_min_y);
	m_range[3].push(m_max_y);
}
