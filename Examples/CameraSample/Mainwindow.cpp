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

	//设置相机2d模式
	//mRender->cameraManage->SetCameraMode(AMCAXRender::CameraMode::k2d);
	//设置相机3d模式
	//mRender->cameraManage->SetCameraMode(AMCAXRender::CameraMode::k3d);

	//double center[3] = { 0.0, 0.0, 0.0 };
	//double directionZ[3] = { 0.0, 0.0, 1.0 };
	//double directionX[3] = { 1.0, 0.0, 0.0 };
	////设置草图坐标系
	//mRender->cameraManage->SetSketchMode(center, directionZ, directionX);
	////设置平行投影
	//mRender->cameraManage->SetParallelProjection(true);
	////设置透视投影
	mRender->cameraManage->SetParallelProjection(false);
	////重置相机视角
	//mRender->cameraManage->ResetCamera();
	////设置相机位置
	//mRender->cameraManage->setPosition(10, 10, 10);
	////设置相机焦点
	//mRender->cameraManage->SetFocalPoint(10, 10, 10);
	////设置相机上方向
	//mRender->cameraManage->SetViewUp(10, 10, 10);
	////沿上方向旋转相机
	//mRender->cameraManage->Azimuth(30);
	////沿右方向旋转相机
	//mRender->cameraManage->Elevation(30);
	////设置相机近远裁剪平面
	//mRender->cameraManage->SetClippingRange(0.1, 100);
	////设置相机视角
	//mRender->cameraManage->SetCameraView(AMCAXRender::CameraView::BACK);
	//mRender->cameraManage->SetCameraView(AMCAXRender::CameraView::FRONT);
	//mRender->cameraManage->SetCameraView(AMCAXRender::CameraView::DOWN);
	//mRender->cameraManage->SetCameraView(AMCAXRender::CameraView::UP);
	//mRender->cameraManage->SetCameraView(AMCAXRender::CameraView::LEFT);
	//mRender->cameraManage->SetCameraView(AMCAXRender::CameraView::RIGHT);
	//重置相机裁剪平面
	mRender->cameraManage->ResetClippingRange();
	mRender->entityManage->DoRepaint();

}

Mainwindow::~Mainwindow()
{

}
