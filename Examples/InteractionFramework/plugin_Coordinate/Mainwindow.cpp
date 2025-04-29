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


	//创建坐标系
	double pos[3] = { 0,0,0 };
	double directx[3] = { 1,0,0 };
	double directz[3] = { 0,0,1 };
	double colorx[3] = { 1,0,1 };
	double colory[3] = { 1,1,1 };
	double colorz[3] = { 1,1,0 };

	auto id = mRender->pluginManage->AddPluginFromType(AMCAXRender::PluginType::kCoordinate);
	auto att = mRender->pluginManage->GetProperty<AMCAXRender::CoordinateProp>(id);
	att->SetParams(pos, directz, directx, colorx, colory, colorz);
	att->SetLength(5);
	mRender->pluginManage->SetProperty(id, att);	
	mRender->cameraManage->ResetCamera();
	mRender->entityManage->DoRepaint();
}

Mainwindow::~Mainwindow()
{

}
