#include "LightPropertyView.h"
#include "ColorPicker.h"
#include "LightModel.h"

#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QTableWidget>
#include <QComboBox>
#include <QHeaderView>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QGroupBox>
#include <QCheckBox>
#include <QSpinBox>

const int QSlider_Range = 10;

enum TableColumn {
    COLUMN_NAME = 0,
    COLUMN_ID = 1
};

LightPropertyView::LightPropertyView(std::shared_ptr<AMCAXRender::LightManager> lightManager, QWidget* parent)
    : QWidget(parent)
{
    //setWindowTitle("Light Property Setting");

    m_lightManager = lightManager;

    m_mainLayout = new QVBoxLayout(this);
    m_mainLayout->setAlignment(Qt::AlignTop);
    m_mainLayout->setSpacing(10);
    this->setLayout(m_mainLayout);

    initUI();
    createDefaultLight();
    //moveToRight(parent);
    setupUI();
    show();
}

void LightPropertyView::closeEvent(QCloseEvent* event)
{
    hide();
}

void LightPropertyView::createDefaultLight()
{
    m_curLight = m_lightManager->CreateLight();
    m_curLight->SetPostion({ 20, 0,0 });
    m_curLight->SetLightEnable(true);
    m_defaultLightName = QString("Light_%1").arg(m_curLight->GetLightID());
    m_lightModel->addLight(m_curLight);
}

void LightPropertyView::moveToRight(QWidget* parent)
{
    if (parent)
    {
        QPoint p = parent->rect().topRight();
        QPoint parentRight = mapToGlobal(p);
        QPoint p1 = rect().topRight();
        QPoint childParent = mapToGlobal(p1);
        int x = parentRight.x() - childParent.x() - rect().width();
        int y = parentRight.y() - childParent.y();
        move(x, y);
    }
}

void LightPropertyView::initUI()
{
    initLightTable();

    initType();
    initParameter();
    initPostion();
    initIntensity();
    initSpot();
}

void LightPropertyView::setupUI()
{
    onTypeChanged(0);
    m_tableView->selectRow(0);
}

void LightPropertyView::initType()
{
    // 类型下拉框
    m_typeCombo = new QComboBox;
    m_typeCombo->addItems({ "Direction", "Point", "Spot" });
    QGroupBox* typeGroup = new QGroupBox("Type");
    QVBoxLayout* typeLayout = new QVBoxLayout(typeGroup);
    typeLayout->addWidget(m_typeCombo);
    
    m_mainLayout->addWidget(typeGroup);

    connect(m_typeCombo, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, &LightPropertyView::onTypeChanged);
}

void LightPropertyView::onTypeChanged(int curr)
{
    if (m_curLight)
    {
        m_curLight->SetType((AMCAXRender::LightType)curr);
        auto light = m_lightModel->getLight(m_currentRow);
        light->type = curr;
    }
    switch (curr)
    {
    case 0:
        m_spotGroup->setEnabled(false);
        m_intensityGroup->setEnabled(false);

        break;
    case 1:
        m_spotGroup->setEnabled(false);
        m_intensityGroup->setEnabled(true);
        break;
    case 2:
        m_spotGroup->setEnabled(true);
        m_intensityGroup->setEnabled(true);
        break;
    default:
        break;
    }
}

void LightPropertyView::initPostion()
{
    // 位置编辑框
    QGroupBox* position = new QGroupBox("Position");
    QFormLayout* rightLayout = new QFormLayout(position);
    m_editX = new QLineEdit("0");
    m_editY = new QLineEdit("0");
    m_editZ = new QLineEdit("0");
    rightLayout->addRow("Position X:", m_editX);
    rightLayout->addRow("Position Y:", m_editY);
    rightLayout->addRow("Position Z:", m_editZ);
    m_mainLayout->addWidget(position);

    connect(m_editX, &QLineEdit::textChanged, [this](const QString& text) {
        m_position[0] = text.toFloat();
        m_curLight->SetPostion(m_position);
        });
    connect(m_editY, &QLineEdit::textChanged, [this](const QString& text) {
        m_position[1] = text.toFloat();
        m_curLight->SetPostion(m_position);
        });
    connect(m_editZ, &QLineEdit::textChanged, [this](const QString& text) {
        m_position[2] = text.toFloat();
        m_curLight->SetPostion(m_position);
        });

    bindLineEdit(m_editX, [](std::shared_ptr< Light> light, float val) { light->position[0] = val; });
    bindLineEdit(m_editY, [](std::shared_ptr< Light> light, float val) { light->position[1] = val; });
    bindLineEdit(m_editZ, [](std::shared_ptr< Light> light, float val) { light->position[2] = val; });
}

void LightPropertyView::initIntensity()
{
    //intensity 编辑
    m_intensityGroup = new QGroupBox("Intensity");
    m_constantAtten = new QSlider(Qt::Horizontal);
    m_constantAtten->setRange(0, QSlider_Range);
    m_linearAtten = new QSlider(Qt::Horizontal);
    m_linearAtten->setRange(0, QSlider_Range);
    m_quadraticAtten = new QSlider(Qt::Horizontal);
    m_quadraticAtten->setRange(0, QSlider_Range);
    QVBoxLayout* intensityLayout = new QVBoxLayout();
    intensityLayout->addWidget(m_constantAtten);
    intensityLayout->addWidget(m_linearAtten);
    intensityLayout->addWidget(m_quadraticAtten);
    m_intensityGroup->setLayout(intensityLayout);
    m_mainLayout->addWidget(m_intensityGroup);

    connect(m_constantAtten, &QSlider::valueChanged, [this](int value) {
        m_constantAttenuation = value;
        m_curLight->SetAttenuation({ m_constantAttenuation, m_linearAttenuation, m_quadraticAttenuation });
        auto light = m_lightModel->getLight(m_currentRow);
        light->constantAtten = value;
        });
    connect(m_linearAtten, &QSlider::valueChanged, [this](int value) {
        m_linearAttenuation = value;
        m_curLight->SetAttenuation({ m_constantAttenuation, m_linearAttenuation, m_quadraticAttenuation });
        auto light = m_lightModel->getLight(m_currentRow);
        light->linearAtten = value;
        });
    connect(m_quadraticAtten, &QSlider::valueChanged, [this](int value) {
        m_quadraticAttenuation = value;
        m_curLight->SetAttenuation({ m_constantAttenuation, m_linearAttenuation, m_quadraticAttenuation });
        auto light = m_lightModel->getLight(m_currentRow);
        light->quadraticAtten = value;
        });
}

void LightPropertyView::initSpot()
{
    //spot 参数编辑
    m_spotGroup = new QGroupBox("spot");
    QGridLayout* spotLayout = new QGridLayout(m_spotGroup);
    spotLayout->addWidget(new QLabel("Angle"), 0, 0);
    auto angleEdit = new QSpinBox(m_spotGroup);
    angleEdit->setRange(0, 90);
    spotLayout->addWidget(angleEdit, 0, 1);
    spotLayout->addWidget(new QLabel("FocalPointX"), 1, 0);
    m_focalX = new QDoubleSpinBox(m_spotGroup);
    m_focalX->setRange(-200.0, 200.0);
    spotLayout->addWidget(m_focalX, 1, 1);
    spotLayout->addWidget(new QLabel("FocalPointY"), 2, 0);
    m_focalY = new QDoubleSpinBox(m_spotGroup);
    m_focalY->setRange(-200.0, 200.0);
    spotLayout->addWidget(m_focalY, 2, 1);
    spotLayout->addWidget(new QLabel("FocalPointZ"), 3, 0);
    m_focalZ = new QDoubleSpinBox(m_spotGroup);
    m_focalZ->setRange(-200.0, 200.0);
    spotLayout->addWidget(m_focalZ, 3, 1);
    m_mainLayout->addWidget(m_spotGroup);

    m_exponenEdit = new QSlider(Qt::Horizontal);
    m_exponenEdit->setRange(0, 100);
    spotLayout->addWidget(m_exponenEdit);

    connect(angleEdit, &QSpinBox::valueChanged, [this](int val) {
        auto light = m_lightModel->getLight(m_currentRow);
        light->spotAngle = (float)val;
        m_curLight->SetSpotConeAngle((float)val);
        });
    connect(m_focalX, &QDoubleSpinBox::valueChanged, [this](double x) {
        auto light = m_lightModel->getLight(m_currentRow);
        light->focalPoint[0] = (float)x;
        m_curLight->SetFocalPoint(light->focalPoint);
    });
    connect(m_focalY, &QDoubleSpinBox::valueChanged, [this](double x) {
        auto light = m_lightModel->getLight(m_currentRow);
        light->focalPoint[1] = (float)x;
        m_curLight->SetFocalPoint(light->focalPoint);
        });
    connect(m_focalZ, &QDoubleSpinBox::valueChanged, [this](double x) {
        auto light = m_lightModel->getLight(m_currentRow);
        light->focalPoint[2] = (float)x;
        m_curLight->SetFocalPoint(light->focalPoint);
        });
    connect(m_exponenEdit, &QSlider::valueChanged, [this](int val) {
        auto light = m_lightModel->getLight(m_currentRow);
        light->spotExponent = (float)val;
        m_curLight->SetSpotExponent((float)val);
        });
}

void LightPropertyView::initParameter()
{
    // 颜色编辑框
    QGroupBox* paramGroup = new QGroupBox("Parameter");
    QVBoxLayout* paramLayout = new QVBoxLayout(paramGroup);

    // 创建三个颜色选择器
    m_colorPicker = new ColorPicker("Color");

    // 添加到布局
    paramLayout->addWidget(m_colorPicker);

    m_mainLayout->addWidget(paramGroup);

    connect(m_colorPicker, &ColorPicker::colorChanged, [this](const QColor& color) {
        m_color = color;
        m_curLight->SetColor({ m_color.redF() , m_color.greenF() , m_color.blueF() });

        auto light = m_lightModel->getLight(m_currentRow);
        std::array<float, 3> diffuse = { color.redF(), color.greenF(), color.blueF() };
        light->diffuse = diffuse;
        });
}

void LightPropertyView::initLightTable()
{
    m_tableView = new QTableView();
    m_lightModel = new LightModel(this);
    m_tableView->setModel(m_lightModel);
    m_tableView->horizontalHeader()->setVisible(true);
    m_tableView->horizontalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;color:black;}");
    m_tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_mainLayout->addWidget(m_tableView);

    auto createButton = new QPushButton("create");
    m_destroyButton = new QPushButton("destroy");

    QHBoxLayout* hLayout = new QHBoxLayout();
    hLayout->addWidget(createButton);
    hLayout->addWidget(m_destroyButton);
    m_mainLayout->addLayout(hLayout);

    connect(createButton, &QPushButton::clicked, [this]() {
        createLight();
        });
    connect(m_destroyButton, &QPushButton::clicked, [this]() {
        QModelIndexList selected = m_tableView->selectionModel()->selectedRows();
        if (!selected.isEmpty()) {
            for (const auto& select : selected)
            {
                QModelIndex cellIndex = m_lightModel->index(select.row(), 1);
                auto rows = m_lightModel->rowCount();
                m_lightManager->RemoveLight(m_lightModel->data(cellIndex).toInt());
                m_lightModel->removeLight(select.row());
            }
        }
        });
    connect(m_tableView->selectionModel(), &QItemSelectionModel::currentRowChanged,
        this, &LightPropertyView::onRowChanged);
}

void LightPropertyView::createLight()
{
    m_curLight = m_lightManager->CreateLight();
    m_curLight->SetLightEnable(true);
    m_lightModel->addLight(m_curLight);
}

void LightPropertyView::apply()
{
    if (m_curLight)
    {
        m_curLight->SetColor({ m_color.redF() , m_color.greenF() , m_color.blueF() });
    }
}

void LightPropertyView::onRowChanged(const QModelIndex current) {
    m_currentRow = current.row();
    if (m_currentRow == -1) return;

    // 从模型获取数据并显示
    auto light = m_lightModel->getLight(m_currentRow);
    m_editX->setText(QString::number(light->position[0]));
    m_editY->setText(QString::number(light->position[1]));
    m_editZ->setText(QString::number(light->position[2]));
    QColor color;
    color.setRgbF(light->diffuse[0], light->diffuse[1], light->diffuse[2]);
    m_colorPicker->setColor(color);
    //color.setRgbF(light->ambient[0], light->ambient[1], light->ambient[2]);
    //m_ambientPicker->setColor(color);
    //color.setRgbF(light->specular[0], light->specular[1], light->specular[2]);
    //m_specularPicker->setColor(color);
    m_typeCombo->setCurrentIndex(light->type);

    m_constantAtten->setValue(light->constantAtten);
    m_linearAtten->setValue(light->linearAtten);
    m_quadraticAtten->setValue(light->quadraticAtten);
    if (light->name == m_defaultLightName)
    {
        m_destroyButton->setEnabled(false);
    }
    else
    {
        m_destroyButton->setEnabled(true);
    }

}
