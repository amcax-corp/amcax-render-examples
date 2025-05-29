#pragma once

#include <QMainWindow>
#include "ui_MWindow.h"
#include"common.h"

#include "DlgMeasurement.h"
#include<QActionGroup>
class MWindow : public QMainWindow
{
	Q_OBJECT

public:
	MWindow(QWidget *parent = nullptr);
	~MWindow();

	void LoadModel();

	//����ʵ��id����
	AMCAX::TopoShape FindToposhaeById(AMCAXRender::EntityId id) {
		if (mShapsSet.count(id) > 0) {
			return mShapsSet[id];
		}
		return AMCAX::TopoShape();
	}
protected:
	void logMessage(const QString& message);
private:
	Ui::MWindowClass ui;

	std::shared_ptr<AMCAXRender::IRenderComponent> mRenderComponent;
	std::shared_ptr<AMCAXRender::CBasicRender> mRender;

	DlgMeasurement* dlgDistance;
	QActionGroup* mActGroup;

	//ʵ��id��Toposhapeӳ���ϵ
	std::unordered_map<AMCAXRender::EntityId, AMCAX::TopoShape> mShapsSet;

};
