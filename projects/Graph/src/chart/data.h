#ifndef DATA_H
#define DATA_H

/** ���ʽṹ */
struct Probability
{
	/** ��λ�� */
	int index;
	/** ����ֵ */
	double theory;
	/** ����CDF */
	double theory_cdf;
	/** ����Zֵ */
	double theory_z;
	/** ʵ��ֵ */
	double reality;
	/** ʵ��CDF */
	double reality_cdf;
	/** ʵ��Zֵ */
	double reality_z;
};

/** ���ַ��� */
enum ScoreType
{
	Blom,
	Benard,
	Hazen,
	VanDerWaerden,
	KaplanMeier
};

/** ��Ʊͼ���� */
struct CandlestickData
{
	CandlestickData(double timestamp, double open, double high, double low, double close)
	{
		m_timestamp = timestamp;
		m_open = open;
		m_high = high;
		m_low = low;
		m_close = close;
	}
	double m_timestamp;
	double m_open;
	double m_high;
	double m_low;
	double m_close;
};

/** ��״ͼ���� */
struct PieData
{
	PieData(QString name, double value)
	{
		m_name = name;
		m_value = value;
	}
	QString m_name;
	double m_value;
};

/** 3d���� */
struct ThirdDData
{
	ThirdDData(double x, double y,double z)
	{
		m_x = x;
		m_y = y;
		m_z = z;
	}
	double m_x;
	double m_y;
	double m_z;
};

/** ����ͼ���� */
struct BoxData
{
	QString m_name;
	QList<double> m_value_list;
};

/** ����ͼ */
enum BoxBarType
{
	MEAN,
	SUM,
	MAX,
	MIN
};

#endif //DATA_H
