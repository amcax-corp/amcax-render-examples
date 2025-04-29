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


	//创建包围盒标注
	auto id = mRender->pluginManage->AddPluginFromType(AMCAXRender::PluginType::kBoundsAnnocation);
	auto att = mRender->pluginManage->GetProperty<AMCAXRender::BoundAnnocationProp>(id);
	AMCAXRender::BoundAnnocationProp::BoxParams box;
	box.center = { 0,0,0 };
	box.len = 5;
	box.width = 10;
	box.hight = 2;
	box.center = { -20,-20,-20 };
	box.directionX = { 1,0,0 };
	box.directionY = { 0,1,0 };

	AMCAXRender::BoundAnnocationProp::SphereParams sphere;
	sphere.center = { 20,20,20 };
	sphere.radius = 10;

	AMCAXRender::BoundAnnocationProp::CylinderParams cylinder;
	cylinder.center1 = { 0,0,0 };
	cylinder.center2 = { 10,0,0 };
	cylinder.radius = 5;
	cylinder.normal = { 1,0,0 };

	att->SetBoxParameter(box);
	att->SetSphereParameter(sphere);
	att->SetCylinderParameter(cylinder);
	att->SetColor({ 0,0,1 });
	att->SetPointSize(20);
	att->SetUnit("mm");
	//att->SetTopRender(true);

	mRender->pluginManage->SetProperty(id, att);

	
	mRender->cameraManage->ResetCamera();
	mRender->entityManage->DoRepaint();
}

Mainwindow::~Mainwindow()
{

}
