#include "Mainwindow.h"
#include <modeling/MakeBox.hpp>
#include <modeling/MakeCylinder.hpp>
#include <QColorDialog>

Mainwindow::Mainwindow(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	//初始化
	mRenderComponent = AMCAXRender::CreateRenderComponent(this);
	mRender = mRenderComponent->CreateBasicRender();

	//窗口布局
	ui.gridLayout_2->setColumnStretch(0, 1);
	ui.gridLayout_2->setColumnMinimumWidth(1,200);
	ui.gridLayout->addWidget(mRender->widget);

	material = mRender->materialManager->CreateMaterial();
	connect(ui.colorButton, &QPushButton::clicked, this, &Mainwindow::onColorButtonClicked);
	connect(ui.importButton, &QPushButton::clicked, this, &Mainwindow::handleOpenFile);
	connect(ui.ambientSlider, &QSlider::valueChanged, this, &Mainwindow::onAmbientSliderChanged);
	connect(ui.diffuseSlider, &QSlider::valueChanged, this, &Mainwindow::onDiffuseSliderChanged);
	connect(ui.specularSlider, &QSlider::valueChanged, this, &Mainwindow::onSpecularSliderChanged);
	connect(ui.specularPowerSlider, &QSlider::valueChanged, this, &Mainwindow::onSpecularPowerSliderChanged);
}

Mainwindow::~Mainwindow()
{

}

void Mainwindow::onColorButtonClicked() 
{
	QColor color = QColorDialog::getColor();
	if (color.isValid()) {
		for (auto& id : entityIds)
		{
			double c[3] = { color.redF(), color.greenF(), color.blueF() };
			mRender->entityManage->SetEntityColor(id, c);
		}
	}
	mRender->styleManage->SetRenderMode(AMCAXRender::RenderMode::Shaded);
	mRender->entityManage->DoRepaint();
}



void Mainwindow::handleOpenFile()
{
	auto shape = AMCAX::MakeCylinder(5,15).Shape();
	auto entity = mRender->entityFactory->FromShape(shape);
	mRender->entityManage->AddEntity(entity);

	entityIds.push_back(entity->GetEntityId());

	mRender->cameraManage->ResetCamera();
	mRender->entityManage->DoRepaint();
}


void Mainwindow::onAmbientSliderChanged(int value) 
{
	QSlider* slider =  ui.ambientSlider;
	double mappedValue = static_cast<double>(value - slider->minimum()) /
		(slider->maximum() - slider->minimum());
	
	material->SetAmbient(mappedValue);
	for (auto& id : entityIds)
	{
		mRender->entityManage->SetMaterial(id, material);
	}
	mRender->entityManage->DoRepaint();
}


void Mainwindow::onDiffuseSliderChanged(int value)
{
	QSlider* slider = ui.diffuseSlider;
	double mappedValue = static_cast<double>(value - slider->minimum()) /
		(slider->maximum() - slider->minimum());

	material->SetDiffuse(mappedValue);
	for (auto& id : entityIds)
	{
		mRender->entityManage->SetMaterial(id, material);
	}

	mRender->entityManage->DoRepaint();
}

void Mainwindow::onSpecularSliderChanged(int value)
{
	QSlider* slider = ui.specularSlider;
	double mappedValue = static_cast<double>(value - slider->minimum()) /
		(slider->maximum() - slider->minimum());

	material->SetSpecular(mappedValue);
	for (auto& id : entityIds)
	{
		mRender->entityManage->SetMaterial(id, material);
	}
	mRender->entityManage->DoRepaint();
}


void Mainwindow::onSpecularPowerSliderChanged(int value)
{
	QSlider* slider = ui.specularPowerSlider;
	double mappedValue = static_cast<double>(value - slider->minimum()) /
		(slider->maximum() - slider->minimum());

	material->SetSpecularPower(mappedValue*128);
	for (auto& id : entityIds)
	{
		mRender->entityManage->SetMaterial(id, material);
	}
	mRender->entityManage->DoRepaint();
}