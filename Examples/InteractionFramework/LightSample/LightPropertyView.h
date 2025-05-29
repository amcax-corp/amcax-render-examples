#pragma once

#include <QtWidgets/qwidget.h>
#include <QVBoxLayout>
#include <QLineEdit>

#include "Interface/LightManager.h"
#include "LightModel.h"

class LightModel;
class QTableView;
class QTableWidget;
class QGroupBox;
class QComboBox;
class ColorPicker;
class QSlider;
class QDoubleSpinBox;
class QPushButton;

class LightPropertyView : public QWidget
{
	Q_OBJECT
public:
	explicit LightPropertyView(std::shared_ptr<AMCAXRender::LightManager> render, QWidget* parent = nullptr);

protected:
	void closeEvent(QCloseEvent* event) override;

private Q_SLOTS:
	void onTypeChanged(int current);
	void createLight();
	void apply();
	void onRowChanged(QModelIndex index);

private:
	void initUI();
	void initType();
	void initPostion();
	void initIntensity();
	void initSpot();
	void initParameter();
	void initLightTable();

	void setupUI();

	void createDefaultLight();

	void moveToRight(QWidget* parent);

	template <typename Setter>
	void bindLineEdit(QLineEdit* editor, Setter set)
	{
		connect(editor, &QLineEdit::textChanged, [=](const QString& str) {
			if (m_currentRow == -1)
			{
				return;
			}
			auto light = m_lightModel->getLight(m_currentRow);
			bool ok;
			float value = str.toFloat(&ok);
			if (ok) {
				set(light, value);
				m_lightModel->updateLight(m_currentRow, light);
				editor->setStyleSheet("");
			}
			else {
				editor->setStyleSheet("background-color: #FFE4E1;");
			}
			});
	}

	std::shared_ptr<AMCAXRender::LightManager> m_lightManager;
	std::shared_ptr<AMCAXRender::Light> m_curLight;

	LightModel* m_lightModel;
	QTableView* m_tableView;

	QVBoxLayout* m_mainLayout;
	QTableWidget* m_lightTable;
	QComboBox* m_typeCombo;
	QGroupBox* m_spotGroup;
	QGroupBox* m_intensityGroup;

	QLineEdit* m_editX;
	QLineEdit* m_editY;
	QLineEdit* m_editZ;

	ColorPicker* m_colorPicker;

	QSlider* m_constantAtten;
	QSlider* m_linearAtten;
	QSlider* m_quadraticAtten;

	std::array<float, 3>  m_position{0.0, 0.0, 0.0};

	QColor m_color;

	QPushButton* m_destroyButton;

	float m_constantAttenuation{ 1.0 };
	float m_linearAttenuation{ 0.0 };
	float m_quadraticAttenuation{ 0.0 };

	int m_currentRow{ 0 };
	QString m_defaultLightName;
	
	float m_spotAngle{ 30. }; 
	QSlider* m_exponenEdit;

	QDoubleSpinBox* m_focalX;
	QDoubleSpinBox* m_focalY;
	QDoubleSpinBox* m_focalZ;
};
