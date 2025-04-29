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

	//禁用
	mRender->interactionCenter->SetRubberBandStatus(AMCAXRender::RubberBandStatus::Disable);
	//框选拾取持续
	mRender->interactionCenter->SetRubberBandStatus(AMCAXRender::RubberBandStatus::PickPermanent);
	//框选拾取一次
	mRender->interactionCenter->SetRubberBandStatus(AMCAXRender::RubberBandStatus::PickOnce);

	AMCAXRender::RubberBandPickConfig config1;
	//设置正选或反选
	config1.SetMode(AMCAXRender::RubberBandPickConfig::SelectionMode::Normal);
	//设置拾取方式，基于几何相交或者颜色
	config1.SetPickMode(AMCAXRender::RubberBandPickConfig::PickMode::Intersection);
	//设置边界是否包含
	config1.SetIncludeBoundary(false);
	//设置浮窗混合颜色
	config1.SetBlendColor(new unsigned char[3] {0, 255, 0});
	//设置拾取配置（从左到右）
	mRender->styleManage->SetRubberBandPickConfig(1, config1);

	AMCAXRender::RubberBandPickConfig config2;
	config2.SetMode(AMCAXRender::RubberBandPickConfig::SelectionMode::Normal);
	config2.SetPickMode(AMCAXRender::RubberBandPickConfig::PickMode::Intersection);
	config2.SetIncludeBoundary(true);
	config2.SetBlendColor(new unsigned char[3] {255, 0, 0});
	//设置拾取配置（从右到左）
	mRender->styleManage->SetRubberBandPickConfig(0, config2);

	mRender->cameraManage->ResetCamera();
	mRender->entityManage->DoRepaint();
}

Mainwindow::~Mainwindow()
{

}
