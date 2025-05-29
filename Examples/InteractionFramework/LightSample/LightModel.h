#pragma once

#include <QAbstractTableModel>

#include <memory>
#include <Interface/Light.h>

struct Light
{
    QString name;
    int id;
    int type;

    std::array<float, 3> diffuse{1,0,0};
    //std::array<float, 3> ambient{1,1,1};
    //std::array<float, 3> specular{1,1,1};

    std::array<float, 3> position{0,0,0};

    float constantAtten{ 1.0 };
    float linearAtten{ 0.0 };
    float quadraticAtten{ 0.0 };

    float spotAngle{ 30.f };
    float spotExponent{ 1.0f };

    std::array<float, 3> focalPoint{0,0,1};
};

class LightModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit LightModel(QObject* parent) : QAbstractTableModel(parent) {}

    int rowCount(const QModelIndex& parent = QModelIndex()) const override
    {
        return m_lights.size();
    }

    int columnCount(const QModelIndex& parent = QModelIndex()) const override
    {
        return 2;
    }

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole)const override
    {
        if (!index.isValid() || role != Qt::DisplayRole)
        {
            return QVariant();
        }
        std::shared_ptr<Light> light = m_lights[index.row()];
        switch (index.column())
        {
        case 0:
            return light->name;
        case 1:
            return light->id;
        default:
            return QVariant();
        }
    }

    QVariant headerData(int section, Qt::Orientation orientation, int role) const override
    {
        if (role == Qt::DisplayRole && orientation == Qt::Horizontal)
        {
            switch (section)
            {
            case 0:
                return "Name";
            case 1:
                return "ID";
            default:
                return QVariant();
            }
        }
        return QVariant();
    }

    bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override
    {
        if (!index.isValid() || role != Qt::EditRole)
        {
            return false;
        }
        std::shared_ptr<Light> light = m_lights[index.row()];
        switch (index.column())
        {
        case 0:
            light->name = value.toString();
            break;
        case 1:
            light->id = value.toInt();
            break;
        default:
            break;
        }
        emit dataChanged(index, index);
        return true;
    }

    void addLight(std::shared_ptr<AMCAXRender::Light> light)
    {
        beginInsertRows(QModelIndex(), rowCount(), rowCount());
        auto param = extract(light);
        m_lights.append(param);
        endInsertRows();
    }

    void removeLight(int row)
    {
        if (row < 0 || row > rowCount())
        {
            return;
        }
        beginRemoveRows(QModelIndex(), row, row);
        m_lights.remove(row);
        endRemoveRows();
    }

    std::shared_ptr<Light> getLight(int row)
    {
        if (row < 0 || row >= m_lights.size())
        {
            return nullptr;
        }
        return m_lights[row];
    }

    void updateLight(int row, const std::shared_ptr<Light>& newData)
    {
        if (row < 0 || row >= rowCount()) return;

        auto light = m_lights[row];
        light = newData;

        // 通知所有列数据变化
        QModelIndex topLeft = createIndex(row, 0);
        QModelIndex bottomRight = createIndex(row, columnCount() - 1);
        emit dataChanged(topLeft, bottomRight);
    }

    static std::shared_ptr<Light> extract(std::shared_ptr<AMCAXRender::Light> light)
    {
        std::shared_ptr<Light> lit = std::make_shared<Light>();
        QString lightName = QString("Light_%1").arg(light->GetLightID());
        lit->name = lightName;
        lit->id = light->GetLightID();
        //lit->ambient = light->GetAmbient();
        //lit->specular = light->GetSpecular();""
        lit->diffuse = light->GetColor();
        lit->type = (int)light->GetType();
        lit->position = light->GetPosition();
        return lit;
    }

private:
    QVector< std::shared_ptr<Light>> m_lights;
};