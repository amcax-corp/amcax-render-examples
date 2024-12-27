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

	//注册坐标系拾取事件
	mRender->interactionCenter->RegisterMarkerEvent(AMCAXRender::MarkerEvent::cubeViewEvent,
		[&](AMCAXRender::MarkerType markerType) {

		});

	//根据事件Id注销坐标系拾取事件
	mRender->interactionCenter->UnregisterMarkerEvent(2);
	//根据事件类型注销坐标系拾取事件
	mRender->interactionCenter->UnregisterMarkerEvent(AMCAXRender::MarkerEvent::cubeViewEvent);
	//注册移动坐标系事件
	mRender->interactionCenter->RegisterMoveEvent([&](AMCAXRender::EntityId id, double* matrix) {

		});
	//获取当前鼠标的世界坐标
	double worldPos[3];
	mRender->interactionCenter->GetPointByMouse(worldPos);
	//获取当前鼠标的屏幕坐标
	int screenPos[2];
	mRender->interactionCenter->GetPointByWorld(worldPos, screenPos);
	//设置实体的线宽
	mRender->interactionCenter->SetEntityLineWidth(2);


	//注册鼠标事件
	mRender->interactionCenter->RegisterMouseEvent([&](AMCAXRender::MouseEventType t) {

		});
	//根据事件Id注销鼠标事件
	mRender->interactionCenter->UnregisterMouseEvent(1);
	//注销所有鼠标事件
	mRender->interactionCenter->UnregisterMouseEvent();

	//注册焦点事件
	mRender->interactionCenter->RegisterFocusEvent([&]() {});
	//根据事件Id注销焦点事件
	mRender->interactionCenter->UnregisterFocusEvent(1);
	//注销所有焦点事件
	mRender->interactionCenter->UnregisterFocusEvent();
	//设置屏幕截图的文件名
	mRender->interactionCenter->SetScreenShot("C:\\xxx.jpg");


	mRender->cameraManage->ResetCamera();
	mRender->entityManage->DoRepaint();
}

Mainwindow::~Mainwindow()
{

}
