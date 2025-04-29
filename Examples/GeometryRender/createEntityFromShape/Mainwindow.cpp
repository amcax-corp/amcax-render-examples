#include "Mainwindow.h"
#include <modeling/MakeBox.hpp>
Mainwindow::Mainwindow(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	//初始化
	mRenderComponent = AMCAXRender::CreateRenderComponent(this);
	mRender = mRenderComponent->CreateBasicRender();

	//窗口布局
	ui.gridLayout->addWidget(mRender->widget);

	AMCAX::TopoShape s = AMCAX::MakeBox(10.0, 10.0, 10.0);
	auto entity = mRender->entityFactory->FromShape(s);
	mRender->entityManage->AddEntity(entity);
	mRender->cameraManage->ResetCamera();
	mRender->entityManage->DoRepaint();

}

Mainwindow::~Mainwindow()
{

}
