#pragma once

#include <QDialog>
#include "ui_DlgMeasurement.h"
#include <AMCAXRender.h>
#include"common.h"
class  MWindow;
struct PickInfo;

class DlgMeasurement : public QDialog
{
	Q_OBJECT

public:

	//测量类型枚举
	enum MeasureType
	{
		kDistance, //最短距离
		kLength,   //长度，周长
		kSquare,   //面积
		kAngle,    //角度
		kVolume,   //体积

	};

	DlgMeasurement(std::shared_ptr<AMCAXRender::CBasicRender> render, MWindow *parent = nullptr);
	~DlgMeasurement();
		
	void showPage(MeasureType t);

protected:
	void closeEvent(QCloseEvent* event) override;

	void clearData();

	//距离计算
	void calcDistance();

	//长度/周长计算
	void calcLength();

	//面积计算
	void calcSquare();

	//直线夹角计算
	void calcAngle();

	//体积计算
	void calcVolume();

private:
	Ui::DlgMeasurementClass ui;
	std::shared_ptr<AMCAXRender::CBasicRender> mRender;
	MWindow* minWindow;

	PickInfo mPickInf[2];

	MeasureType mCurrentType;

};
