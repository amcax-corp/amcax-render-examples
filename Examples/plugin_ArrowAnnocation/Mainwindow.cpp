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


	//创建距离标注，双箭头
	auto id = mRender->pluginManage->AddPluginFromType(AMCAXRender::PluginType::kArrowAnnocation);
	auto att = mRender->pluginManage->GetProperty<AMCAXRender::ArrowAnnocationProp>(id);
	att->SetPointParameter({ 0,0,0 }, { 10,10,10 }, AMCAXRender::ArrowAnnocationProp::AnnoType::kDistance);
	att->SetLabel(std::wstring(L"距离标注双箭头"));
	att->SetColor({ 0,0,1 });
	att->SetFontSize(20);
	att->SetPointSize(10);
	//att->SetTopRender(true);
	mRender->pluginManage->SetProperty(id, att);


	auto id2 = mRender->pluginManage->AddPluginFromType(AMCAXRender::PluginType::kArrowAnnocation);
	auto att2 = mRender->pluginManage->GetProperty<AMCAXRender::ArrowAnnocationProp>(id);
	att2->SetPointParameter({ -2,0,0 }, { -10,0,10 }, AMCAXRender::ArrowAnnocationProp::AnnoType::kRadius);
	att2->SetLabel(std::wstring(L"半径标注单箭头"));
	att2->SetColor({ 1,0,1 });
	att2->SetFontSize(20);
	att2->SetPointSize(10);
	//att->SetTopRender(true);
	mRender->pluginManage->SetProperty(id2, att2);

	mRender->cameraManage->ResetCamera();
	mRender->entityManage->DoRepaint();
}

Mainwindow::~Mainwindow()
{

}
