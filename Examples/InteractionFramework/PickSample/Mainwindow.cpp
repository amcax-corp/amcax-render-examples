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

	//设置拾取的类型
	mRender->interactionCenter->PickEventFilter(AMCAXRender::PickType::all);
	mRender->interactionCenter->PickEventFilter(AMCAXRender::PickType::edge);
	mRender->interactionCenter->PickEventFilter(AMCAXRender::PickType::point);
	mRender->interactionCenter->PickEventFilter(AMCAXRender::PickType::face);

	//设置拾取颜色
	double c[3] = { 1,1,0 };
	mRender->interactionCenter->SetPickColor(c);
	//注册拾取事件
	mRender->interactionCenter->RegisterPickEvent(AMCAXRender::EventType::mouse_click,
		[&](AMCAXRender::EntityId parentId, AMCAXRender::EntityId entityId, AMCAXRender::PickType type, int subIndex, int* pos) {

		});
	//根据事件Id注销拾取事件
	mRender->interactionCenter->UnregisterPickEvent(2);
	//根据事件类型注销拾取事件
	mRender->interactionCenter->UnregisterPickEvent(AMCAXRender::EventType::mouse_click);

	//设置拾取的线宽
	mRender->interactionCenter->SetPickLineWidth(2);
	//注册拾取事件（从shape生成的实体）
	mRender->interactionCenter->RegisterPickEventfromShape(AMCAXRender::EventType::mouse_click,
		[&](AMCAXRender::EntityId parentId, AMCAXRender::EntityId entityId, AMCAXRender::PickType type, const AMCAX::TopoShape& shape, int* pos) {

		});
	//根据事件Id注销拾取事件（从shape生成的实体）
	mRender->interactionCenter->UnregisterPickEventfromShape(2);
	//根据事件类型注销拾取事件（从shape生成的实体）
	mRender->interactionCenter->UnregisterPickEventfromShape(AMCAXRender::EventType::mouse_click);

	mRender->cameraManage->ResetCamera();
	mRender->entityManage->DoRepaint();
}

Mainwindow::~Mainwindow()
{

}
