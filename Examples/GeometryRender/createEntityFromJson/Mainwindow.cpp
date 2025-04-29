#include "Mainwindow.h"
#include <iostream>
#include <fstream>
#include <interface/Constants.h>
#include <nlohmann/json.hpp>

Mainwindow::Mainwindow(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	//初始化
	mRenderComponent = AMCAXRender::CreateRenderComponent(this);
	mRender = mRenderComponent->CreateBasicRender();

	//窗口布局
	ui.gridLayout->addWidget(mRender->widget);

	std::ifstream file("prism.json");

	if (!file.is_open()) {
		std::cerr << "Failed to open file: prism.json" << std::endl;
		return;
	}

	CAXjson jsonData;
	file >> jsonData;
	auto entity = mRender->entityFactory->FromJson(jsonData);
	mRender->entityManage->AddEntity(entity);
	mRender->cameraManage->ResetCamera();
	mRender->entityManage->DoRepaint();
}

Mainwindow::~Mainwindow()
{

}
