#include "Mainwindow.h"
#include <modeling/MakeBox.hpp>

#include <QGridLayout>
#include <QColorDialog>
#include <QMouseEvent>
#include <iostream>
#include <QDebug>


Mainwindow::Mainwindow(QWidget* parent)
    : QWidget(parent)
{
    //ui.setupUi(this);

    //初始化
    mRenderComponent = AMCAXRender::CreateRenderComponent(this);
    mRender = mRenderComponent->CreateBasicRender();

    QRect rect(800, 600, 800, 600);
    setGeometry(rect);

    QGridLayout* layout = new QGridLayout;
    layout->addWidget(mRender->widget);
    setLayout(layout);


    colorDialog = new QColorDialog(this);
    colorDialog->setVisible(false);

    mRender->styleManage->SetGradientBackground(true);
}

Mainwindow::~Mainwindow()
{

}

void Mainwindow::mouseReleaseEvent(QMouseEvent* event)
{
    //change background color demo

    if (event->button() == Qt::LeftButton)
    {
        QColor color = QColorDialog::getColor();
        if (!color.isValid())
        {
            return;
        }
        float ratio = (float)event->pos().y() / geometry().height();
        if (ratio > 0.5f)
        {
            mRender->styleManage->SetBackground(color.redF(), color.greenF(), color.blueF());
        }
        else
        {
            mRender->styleManage->SetBackground2(color.redF() , color.greenF() , color.blueF() );
        }
        mRender->entityManage->DoRepaint();
    }
}

