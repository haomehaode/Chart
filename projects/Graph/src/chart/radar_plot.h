#ifndef RADAR_PLOT_H
#define RADAR_PLOT_H

#include "plot.h"
#include "graph_global.h"
#include "graphics_item.h"
#include <QCategoryAxis>
#include <QValueAxis>
#include <QLineSeries>

enum RadarType
{
	Radar = 0,  //�״�ͼ
	Spider		//֩����ͼ
};

enum PointTpye
{
	ScatterPoints = 0,	//ɢ��ͼ
	LinePoints			//����ͼ
};

enum FillType
{
	Fill = 0,	//���
	Empty		//��
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

protected:

	virtual void init_chart() override;

	virtual void init_axis() override;

	virtual void init_series() override;

private:
	/** �Ƕ�ֵ */
	QCategoryAxis* m_angularAxis = nullptr;
	/** �״�ֵ */
	QValueAxis* m_radialAxis = nullptr;
	/** ͼ���� */
	RadarType m_radartype = Radar;
	/** ������ */
	PointTpye m_pointstype = LinePoints;
	/** ������� */
	FillType m_filltype = Fill;
	/** �״����� */
	int count = 0;
	/** ���ƺ�ϵ��ӳ�� */
	QMap<QString, QLineSeries*> m_name2series;
};

#endif // RADAR_PLOT_H