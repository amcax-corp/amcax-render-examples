#include "Mainwindow.h"

Mainwindow::Mainwindow(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	//初始化
	mRenderComponent = AMCAXRender::CreateRenderComponent(this);
	mRender = mRenderComponent->CreateBasicRender();

	//窗口布局
	ui.gridLayout->addWidget(mRender->widget);

	//创建文本
	auto id  = mRender->pluginManage->AddPluginFromType(AMCAXRender::PluginType::kTextLabel);
	auto att = mRender->pluginManage->GetProperty<AMCAXRender::TextLabelProp>(id);
	att->AddText("hello 1", { 0,0,0 }, { 1,0,0 });
	att->AddText("hello 2", { 1,0,0 }, { 1,1,0 });
	att->SetFontSize(50);
	att->SetOpacity(0.5);
	//att->SetTopRender(true);
	mRender->pluginManage->SetProperty(id, att);
	mRender->cameraManage->ResetCamera();
	mRender->entityManage->DoRepaint();
}

Mainwindow::~Mainwindow()
{

}
