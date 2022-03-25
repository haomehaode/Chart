#ifndef RADAR_PLOT_H
#define RADAR_PLOT_H

#include "plot.h"
#include "graph_global.h"
#include "graphics_item.h"
#include <QCategoryAxis>
#include <QValueAxis>
#include <QLineSeries>
#include <QScatterSeries>
#include <QAreaSeries>

enum RadarType
{
	Radar = 0,  //�״�ͼ
	Spider		//֩����ͼ
};

enum DrawTpye
{
	Scatter = 0,	//ɢ��ͼ
	Line,			//����ͼ
	Area			//����ͼ
};

//////////////////////////////////////////////////////////////////////////////
/// �״�ͼ
class RadarItem :public GraphicsItem
{
	Q_OBJECT

public:
	RadarItem();
	void set_chart(QChart* chart);
	void set_radial(int radial);
	void set_angular(int angular);

protected:
	QRectF boundingRect() const override;
	void on_paint(QPainter* painter) override;

private:
	QChart* m_chart = nullptr;
	/** �״����� */
	int m_angular = 5;
	/** �״�Ȧ�� */
	int m_radial = 6;
};


class GRAPH_EXPORT RadarPlot : public Plot
{
	Q_OBJECT

public:

	RadarPlot(QWidget* parent = nullptr);

	~RadarPlot();

	void set_radar(QStringList& lablelist);

	void add_radar(QList<double>& valuelist, const QString& name);

	void delete_radar(const QString& name);

	void set_radar_type(RadarType type);


protected:

	virtual void init_chart() override;

	virtual void init_axis() override;

	virtual void init_series() override;

private:
	/** ֩����ͼ */
	RadarItem* item = nullptr;
	/** �Ƕ�ֵ/�״��� */
	QCategoryAxis* m_angularAxis = nullptr;
	/** �״�ֵ/�״�Ȧ�� */
	QValueAxis* m_radialAxis = nullptr;
	/** ͼ���� */
	RadarType m_radartype = Spider;
	/** ������ */
	DrawTpye m_drawtype = Line;
	/** �״����� */
	int count = 0;
	/** ���ƺ�ϵ��ӳ�� */
	QMap<QString, QLineSeries*> m_name2series;
};

#endif // RADAR_PLOT_H