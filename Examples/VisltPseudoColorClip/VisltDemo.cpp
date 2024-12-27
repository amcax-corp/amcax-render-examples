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

    //设置背景颜色
    render->styleManage->SetGradientBackground(false);
    render->styleManage->SetBackground(1, 1, 1);

    //创建云图对象
    auto vislt = render->cloudVisltFactory->ReadFile("meshtally.vtk");

    //获取云图对象标量名称
    auto names = vislt->GetScalarNames();

    //添加云图对象到渲染场景
    auto id = render->cloudVisltManage->AddCloudVislt(vislt, names[0]);

    //隐藏云图对象
    render->cloudVisltManage->SetVisible(id, false);

    int* dim = vislt->GetDimensions();
    double* spaceing = vislt->GetSpacing();
    double* origin = vislt->GetOrigin();

    std::cout << "dim : " << dim[0] << " " << dim[1] << " " << dim[2] << std::endl;
    std::cout << "spaceing : " << spaceing[0] << " " << spaceing[1] << " " << spaceing[2] << std::endl;
    std::cout << "origin : " << origin[0] << " " << origin[1] << " " << origin[2] << std::endl;

    //设置裁剪属性
    AMCAXRender::ClipAttributes clip;
    clip.SetQuality(AMCAXRender::ClipAttributes::Fast);
    double normal1[3] = { 1,0,0 };
    double origin1[3] = { 10000, 0, 0 };
    clip.SetPlane1Status(true);
    clip.SetPlane1Normal(normal1);
    clip.SetPlane1Origin(origin1);

    double normal2[3] = { 0,1,0 };
    double origin2[3] = { 0, -12000, 0 };
    clip.SetPlane2Status(true);
    clip.SetPlane2Origin(origin2);
    clip.SetPlane2Normal(normal2);

    double normal3[3] = { 0,0,1 };
    double origin3[3] = { 0, 0, 4000 };
    clip.SetPlane3Status(true);
    clip.SetPlane3Origin(origin3);
    clip.SetPlane3Normal(normal3);

    //计算裁剪
    render->cloudVisltManage->GetProperty(id)->ComputeClip(clip);

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