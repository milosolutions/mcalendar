/*******************************************************************************
Copyright (C) 2017 Milo Solutions
Contact: https://www.milosolutions.com

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*******************************************************************************/



#include <QApplication>
#include <QLoggingCategory>
#include <QDebug>
#include <QHBoxLayout>
#include <QLabel>
#include <QString>
#include <QPushButton>
#include "mcalendar.h"

Q_LOGGING_CATEGORY(coreMain, "core.main")

class SampleDay : public MSimpleDay
{
public:
    SampleDay()
    {
        auto layout = new QVBoxLayout(this);
        m_label = new QLabel;
        m_label->setFixedWidth(50);
        layout->addWidget(m_label);
    }


protected:
    virtual void onDateChanged() override
    {
        qCDebug(coreMain) << "Date has changed!" << date();
    }

    QLabel* m_label;
};

using SampleDayFactory = MGenericFactory<SampleDay, MDayFactory>;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    a.setApplicationName("Example MCalendar app");
    a.setOrganizationName("Milo");

    qCDebug(coreMain) << "Application name is:" << a.applicationName();

    QWidget w;
    QHBoxLayout* layout = new QHBoxLayout ();

    auto date = QDate::currentDate();
    MCalendar calendar;
    calendar.setHeader(new MSimpleHeader(&calendar));
    calendar.setDayFactory(new SampleDayFactory());
    calendar.setRowFactory(new MWeekRowFactory());
    calendar.setMonth(date);

    QPushButton b("Next Month");
    b.connect(&b, &QPushButton::clicked,
        [&]() {
            date = date.addMonths(1);
            calendar.setMonth(date);
        });
        
    layout->addWidget(&calendar);
    layout->addWidget(&b);
    w.setLayout(layout);
    w.show();
    return a.exec();
}
