#ifndef SAMPLEDAY_H
#define SAMPLEDAY_H

#include "mcalendar.h"
#include <QToolButton>

class SampleDay : public MDayView
{
public:
    SampleDay();

    using Factory = MGenericFactory<SampleDay, MDayFactory>;

protected:
    virtual void onDateChanged() override;

    QToolButton* m_button;
};


#endif // SAMPLEDAY_H
