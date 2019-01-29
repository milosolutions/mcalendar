#ifndef TIMERANGE_H
#define TIMERANGE_H

#include <QTime>

/*! \class TimeRange
 *  \brief A class that represents the time range
 */
class TimeRange
{
 public:
    QTime start;
    QTime end;
    TimeRange() {}
    TimeRange(const QTime &start, const QTime &end)
    {
        this->start = start;
        this->end = end;
    }
};

#endif  // TIMERANGE_H
