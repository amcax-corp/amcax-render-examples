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

	//构建线数据
	AMCAXRender::CAXMeshInfo rays;
	rays.category = "SHAPE";
	rays.id = "rays";

	// 顶点坐标，每个面需要四个点，共24个点
	rays.points = {
		{0.0, 0.0, 0.0}, {10.0, 0.0, 0.0}, {10.0, 10.0, 0.0}, {0.0, 10.0, 0.0},
		{0.0, 0.0, 10.0}, {10.0, 0.0, 10.0}, {10.0, 10.0, 10.0}, {0.0, 10.0, 10.0},
	};

	// 边数据
	rays.edges = {
		{"index", {0, 1,2,3,4,5,6,7}}
	};

	auto entity = mRender->entityFactory->FromCAXMeshInfo(rays);
	mRender->entityManage->AddEntity(entity);

	//设置光线宽度
	mRender->entityManage->SetRayFlag(entity->GetEntityId(), true, 3);

	mRender->cameraManage->ResetCamera();
	mRender->entityManage->DoRepaint();
}

Mainwindow::~Mainwindow()
{

}
