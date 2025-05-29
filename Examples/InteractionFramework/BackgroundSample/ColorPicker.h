#include <QApplication>
#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QFrame>
#include <QColorDialog>
#include <QMouseEvent>
#include <QPushButton>

// �Զ�����ɫѡ��ؼ�
class ColorPicker : public QWidget {
    Q_OBJECT

public:
    ColorPicker(const QString& text, QWidget* parent = nullptr)
        : QWidget(parent), color(Qt::black)
    {
        // ���򲼾֣���ǩ + ��ɫ��
        QHBoxLayout* layout = new QHBoxLayout(this);
        layout->setContentsMargins(0, 0, 0, 0);

        QPushButton* pushButton = new QPushButton(parent);
        pushButton->setText(text);
        layout->addWidget(pushButton);

        // ��ɫԤ����
        colorFrame = new QFrame;
        colorFrame->setFixedSize(60, 24);           // ���ù̶���С
        colorFrame->setFrameShape(QFrame::Box);     // �߿���ʽ
        colorFrame->setLineWidth(1);                // �߿���
        colorFrame->setStyleSheet("background-color: " + color.name() + ";");
        layout->addWidget(colorFrame);

        // ��������ǩ������ɫѡ��
        pushButton->installEventFilter(this);
    }

    // ��ȡ��ǰ��ɫ
    QColor getColor() const { return color; }

signals:
    void colorChanged(const QColor& color);

protected:
    bool eventFilter(QObject* obj, QEvent* event) override {
        // �����ǩ����ɫ��ĵ���¼�
        if (event->type() == QEvent::MouseButtonPress) {
            QColor newColor = QColorDialog::getColor(color, this, "ѡ����ɫ");
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