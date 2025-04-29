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

	//设置坐标系风格
	mRender->styleManage->SetMarkerStyle(AMCAXRender::CoordStyle::cubeView);
	mRender->styleManage->SetMarkerStyle(AMCAXRender::CoordStyle::sailView);
	mRender->styleManage->SetMarkerStyle(AMCAXRender::CoordStyle::cubeView2);
	//设置交互风格
	mRender->styleManage->SetIneractoinStyle(AMCAXRender::InteractonStyle::interaction_1);
	mRender->styleManage->SetIneractoinStyle(AMCAXRender::InteractonStyle::interaction_2);


	//设置坐标系是否开启鼠标交互
	mRender->styleManage->SetMarkerInteractive(true);
	mRender->styleManage->SetMarkerInteractive(false);

	//设置标准平面风格
	mRender->styleManage->SetPlaneStyle(AMCAXRender::PlaneStyle::standardPlane);
	mRender->styleManage->SetPlaneStyle(AMCAXRender::PlaneStyle::none);

	//设置背景色1
	mRender->styleManage->SetBackground(1, 0, 0);
	//设置背景色2
	mRender->styleManage->SetBackground2(0, 1, 0);
	//设置是否开启渐进色背景
	mRender->styleManage->SetGradientBackground(true);
	//设置是否开启拾取效果
	mRender->styleManage->SetPickColorEnable(true);

	mRender->cameraManage->ResetCamera();
	mRender->entityManage->DoRepaint();
}

Mainwindow::~Mainwindow()
{

}
