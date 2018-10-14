#include "smallwidget.h"
#include <QSpinBox>
#include <QSlider>
#include <QHBoxLayout>
#include <QDebug>

SmallWidget::SmallWidget(QWidget *parent) : QWidget(parent)
{
    QSpinBox *spin = new QSpinBox(this);
    QSlider *slider = new QSlider(Qt::Horizontal,this);

    //控件水平排列（完成布局）
    QHBoxLayout *hLayout = new QHBoxLayout(this);
    hLayout->addWidget(spin);
    hLayout->addWidget(slider);

    //调节微调框可以使滑块滑动
    void (QSpinBox::*value_signal)(int val) = &QSpinBox::valueChanged;
    //Access functions:void	setValue(int)
    connect(spin, value_signal, slider, &QSlider::setValue);

    //调节滑块移动可以使微调框进行微调
    connect(slider, &QSlider::valueChanged, spin, &QSpinBox::setValue);

}

