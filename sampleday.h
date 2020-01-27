#ifndef SAMPLEDAY_H
#define SAMPLEDAY_H

#include "mcalendar.h"



class SampleDay : public MDayView
{
public:
    SampleDay();

    using Factory = MGenericFactory<SampleDay, MDayFactory>;

protected:
    virtual void onDateChanged() override;

    QLabel* m_label;
};


#endif // SAMPLEDAY_H
