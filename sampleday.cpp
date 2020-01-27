#include "sampleday.h"

#include <QBoxLayout>
#include <QLabel>

#include <QLoggingCategory>

Q_DECLARE_LOGGING_CATEGORY(coreMain)

SampleDay::SampleDay() : MDayView()
{
    auto layout = new QVBoxLayout(this);
    m_label = new QLabel;
    m_label->setFixedWidth(50);
    layout->addWidget(m_label);
}

void SampleDay::onDateChanged()
{
    qCDebug(coreMain) << "Date has changed!" << date();
    m_label->setText(date().toString("d"));
}
