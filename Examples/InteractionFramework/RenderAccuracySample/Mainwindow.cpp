#include "Mainwindow.h"
#include "ui_RenderSetting.h"

#include <iostream>
#include <QDebug>
#include <QCoreApplication>
#include <QDir>

#ifdef USE_AMCAX_KERNEL
#include <step/StepReader.hpp>
#include <step/StepDataTool.hpp>
#include <step/StepData.hpp>
#endif

#include <fstream>

Mainwindow::Mainwindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //初始化
    mRenderComponent = AMCAXRender::CreateRenderComponent(this);
    mRender = mRenderComponent->CreateBasicRender();

	ui->leftLayout->addWidget(mRender->widget);

	ui->doubleSpinBox->setRange(0, 1.0);
	ui->doubleSpinBox->setDecimals(1);
	ui->doubleSpinBox->setValue(1.0);
	ui->doubleSpinBox->setSingleStep(0.1);

	connect(ui->doubleSpinBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
		this, &Mainwindow::onDoubleSpinBoxValueChanged);

	QString setpPath = QCoreApplication::applicationDirPath() + "/accuracy_sample.STEP";

	std::ifstream ifs(std::filesystem::u8path(setpPath.toStdString()));
	AMCAX::STEP::StepReader reader(ifs);

	if (!reader.Read())
		return;

	auto products = AMCAX::STEP::StepDataTool::Flatten(reader.GetShapes());

	for (std::shared_ptr<AMCAX::STEP::StepData> product : products)
	{
		for (const AMCAX::TopoShape& shape : product->Shapes())
		{
			if (!shape.IsNull())
			{
				auto entity = mRender->entityFactory->FromShape(shape);
				mRender->entityManage->AddEntity(entity);
			}
		}
	}

	mRender->cameraManage->ResetCamera();
}

Mainwindow::~Mainwindow()
{
	delete ui;
}

void Mainwindow::onDoubleSpinBoxValueChanged(double value)
{
	qDebug() << "value :" << value;
	mRender->interactionCenter->UseAccuracy(true);
	mRender->interactionCenter->SetAccuracy(value, [this]() {
		qDebug() << "Rendering accuracy complete!";
		}
	);
}
