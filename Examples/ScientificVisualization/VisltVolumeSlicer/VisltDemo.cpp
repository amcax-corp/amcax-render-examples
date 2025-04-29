// VisltDemo.cpp: 定义应用程序的入口点。
//
#include "VisltDemo.h"
#include <QFileDialog>
#include "ui_VisltDemo.h"
#include <iostream>
#include <chrono>
#include <iomanip>
#include <ctime>

VisltDemoWindow::VisltDemoWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //创建引擎
    render = AMCAXRender::CreateRenderComponent(this)->CreateBasicRender();

    setCentralWidget(render->widget);

    //创建云图对象
    auto vislt = render->cloudVisltFactory->ReadFile("FullHead.mhd");

    //获取云图对象标量名称
    auto names = vislt->GetScalarNames();

    //添加云图对象到渲染场景，设置体渲染
    auto id = render->cloudVisltManage->AddCloudVislt(vislt, names[0], 1);

    //隐藏云图对象
    render->cloudVisltManage->SetVisible(id, false);

    //设置切片
    render->cloudVisltManage->GetProperty<AMCAXRender::VisltVolumeProperty>(id)->SetSlicer(2, 50);

    //设置阈值
    auto range = vislt->GetScaleRange(names[0]);
    render->cloudVisltManage->GetProperty<AMCAXRender::VisltVolumeProperty>(id)->SetSlicerThreshold(std::get<0>(range), std::get<1>(range));

    //隐藏映射映射表
    render->cloudVisltManage->SetVisibleColorMap(false);

    //重置相机
    render->cameraManage->ResetCamera();
    //刷新场景
    render->entityManage->DoRepaint();
}

VisltDemoWindow::~VisltDemoWindow()
{
    delete ui;
}

void VisltDemoWindow::handleOpenFile()
{
}