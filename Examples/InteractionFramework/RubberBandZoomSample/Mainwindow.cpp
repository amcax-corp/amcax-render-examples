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

	//框选缩放一次
	mRender->interactionCenter->SetRubberBandStatus(AMCAXRender::RubberBandStatus::Disable);
	//框选缩放持续
	mRender->interactionCenter->SetRubberBandStatus(AMCAXRender::RubberBandStatus::ZoomPermanent);
	//禁用
	mRender->interactionCenter->SetRubberBandStatus(AMCAXRender::RubberBandStatus::ZoomOnce);
	//注册缩放结束回调事件
	mRender->interactionCenter->RegisterRubberBandZoomEvent([&]() {

		});
	//注销缩放事件
	mRender->interactionCenter->UnregisterRubberBandZoomEvent();

	mRender->cameraManage->ResetCamera();
	mRender->entityManage->DoRepaint();
}

Mainwindow::~Mainwindow()
{

}
