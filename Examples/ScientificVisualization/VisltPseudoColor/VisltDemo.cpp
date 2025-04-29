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
    auto vislt = render->cloudVisltFactory->ReadFile("meshtally.vtk");

    //获取云图对象标量名称
    auto names = vislt->GetScalarNames();

    //添加云图对象到渲染场景
    render->cloudVisltManage->AddCloudVislt(vislt, names[0]);

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