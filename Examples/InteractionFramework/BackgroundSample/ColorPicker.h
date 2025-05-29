#include <QApplication>
#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QFrame>
#include <QColorDialog>
#include <QMouseEvent>
#include <QPushButton>

// 自定义颜色选择控件
class ColorPicker : public QWidget {
    Q_OBJECT

public:
    ColorPicker(const QString& text, QWidget* parent = nullptr)
        : QWidget(parent), color(Qt::black)
    {
        // 横向布局：标签 + 颜色框
        QHBoxLayout* layout = new QHBoxLayout(this);
        layout->setContentsMargins(0, 0, 0, 0);

        QPushButton* pushButton = new QPushButton(parent);
        pushButton->setText(text);
        layout->addWidget(pushButton);

        // 颜色预览框
        colorFrame = new QFrame;
        colorFrame->setFixedSize(60, 24);           // 设置固定大小
        colorFrame->setFrameShape(QFrame::Box);     // 边框样式
        colorFrame->setLineWidth(1);                // 边框宽度
        colorFrame->setStyleSheet("background-color: " + color.name() + ";");
        layout->addWidget(colorFrame);

        // 允许点击标签触发颜色选择
        pushButton->installEventFilter(this);
    }

    // 获取当前颜色
    QColor getColor() const { return color; }

signals:
    void colorChanged(const QColor& color);

protected:
    bool eventFilter(QObject* obj, QEvent* event) override {
        // 处理标签或颜色框的点击事件
        if (event->type() == QEvent::MouseButtonPress) {
            QColor newColor = QColorDialog::getColor(color, this, "选择颜色");
            if (newColor.isValid()) {
                color = newColor;
                colorFrame->setStyleSheet("background-color: " + color.name() + ";");
                emit colorChanged(color);
            }
            return true;
        }
        return QWidget::eventFilter(obj, event);
    }

private:
    QFrame* colorFrame;
    QColor color;
};