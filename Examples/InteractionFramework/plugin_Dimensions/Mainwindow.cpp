#include "Mainwindow.h"
#include<iostream>

Mainwindow::Mainwindow(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	//初始化
	mRenderComponent = AMCAXRender::CreateRenderComponent(this);
	mRender = mRenderComponent->CreateBasicRender();

	//窗口布局
	ui.gridLayout->addWidget(mRender->widget);

	connect(ui.pushButton_Linear, &QPushButton::clicked, this, &Mainwindow::CreateLinearDimensions);
	connect(ui.pushButton_angle, &QPushButton::clicked, this, &Mainwindow::CreateAngleDimensions);

}

Mainwindow::~Mainwindow()
{

}

void Mainwindow::CreateLinearDimensions()
{
	auto id = mRender->pluginManage->AddPluginFromType(AMCAXRender::PluginType::kLinearDimension);
	auto att = mRender->pluginManage->GetProperty<AMCAXRender::LinearDimensionProp>(id);

	att->SetBasePlane({ 0,0,0 }, { 1,1,0 });
	mRender->pluginManage->SetProperty(id, att);
	mRender->entityManage->DoRepaint();
	mRender->cameraManage->ResetCamera();

}

void Mainwindow::CreateAngleDimensions()
{
	auto id = mRender->pluginManage->AddPluginFromType(AMCAXRender::PluginType::kAngleDimension);
	auto att = mRender->pluginManage->GetProperty<AMCAXRender::AngleDimensionProp>(id);

	att->SetBasePlane({ 0,0,0 }, { 1,1,0 });
	//att->SetTopRender(1);
	mRender->pluginManage->SetProperty(id, att);
	mRender->entityManage->DoRepaint();
	mRender->cameraManage->ResetCamera();
}