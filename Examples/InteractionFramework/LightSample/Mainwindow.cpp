#include "Mainwindow.h"

#include <QGridLayout>
#include <QColorDialog>
#include <QMouseEvent>
#include <iostream>
#include <QDebug>

#include "LightPropertyView.h"

#ifdef USE_AMCAX_KERNEL
#include <modeling/MakeShapeTool.hpp>
#include <modeling/MakeSphere.hpp>

#endif


Mainwindow::Mainwindow(QWidget* parent)
    : QWidget(parent)
{
    //ui.setupUi(this);

    //初始化
    mRenderComponent = AMCAXRender::CreateRenderComponent(this);
    mRender = mRenderComponent->CreateBasicRender();

    QRect rect(800, 600, 800, 600);
    setGeometry(rect);

    QHBoxLayout* layout = new QHBoxLayout;
    layout->addWidget(mRender->widget, 1);
    mRender->widget->show();
    setLayout(layout);

    colorDialog = new QColorDialog(this);
    colorDialog->setVisible(false);

    m_lightProperty = new LightPropertyView(mRender->lightManager, this);
    layout->addWidget(m_lightProperty, 0);

    CreateSphere();
}

Mainwindow::~Mainwindow()
{

}

void Mainwindow::CreateSphere()
{
#ifdef USE_AMCAX_KERNEL
	AMCAX::TopoShape sphere = AMCAX::MakeSphere(10);
	auto sphereEntity = mRender->entityFactory->FromShape(sphere);
	mRender->entityManage->ClearPreview();
	mRender->entityManage->AddEntity(sphereEntity);
	double rgb[3] = { 1.0, 0.0, 0.0 };
	mRender->entityManage->SetEntityColor(sphereEntity->GetEntityId(), rgb);

	mRender->cameraManage->ResetCamera();
	mRender->styleManage->ShowTitleMenu(0);
	mRender->entityManage->DoRepaint();
#endif // USE_AMCAX_KERNEL
}



