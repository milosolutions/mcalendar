#include "sampleday.h"

#include <QBoxLayout>
#include <QMessageBox>
#include <QLoggingCategory>

Q_DECLARE_LOGGING_CATEGORY(coreMain)

SampleDay::SampleDay() : MDayView()
{
    auto layout = new QVBoxLayout(this);
    m_button = new QToolButton;
    m_button->setFixedWidth(32);

    connect(m_button, &QToolButton::clicked, this,
    [&]() {
        QMessageBox::information(this, "Button Clicked", date().toString());
    });

    layout->addWidget(m_button);
}

void SampleDay::onDateChanged()
{
    //qCDebug(coreMain) << "Date has changed!" << date();
    m_button->setText(date().toString("d"));
}
