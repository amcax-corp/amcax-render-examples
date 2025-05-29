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

	//��������ö��
	enum MeasureType
	{
		kDistance, //��̾���
		kLength,   //���ȣ��ܳ�
		kSquare,   //���
		kAngle,    //�Ƕ�
		kVolume,   //���

	};

	DlgMeasurement(std::shared_ptr<AMCAXRender::CBasicRender> render, MWindow *parent = nullptr);
	~DlgMeasurement();
		
	void showPage(MeasureType t);

protected:
	void closeEvent(QCloseEvent* event) override;

	void clearData();

	//�������
	void calcDistance();

	//����/�ܳ�����
	void calcLength();

	//�������
	void calcSquare();

	//ֱ�߼нǼ���
	void calcAngle();

	//�������
	void calcVolume();

private:
	Ui::DlgMeasurementClass ui;
	std::shared_ptr<AMCAXRender::CBasicRender> mRender;
	MWindow* minWindow;

	PickInfo mPickInf[2];

	MeasureType mCurrentType;

};
