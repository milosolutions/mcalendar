#ifndef DATERANGE_H
#define DATERANGE_H

#include <QDate>

/*! \class DateRange
 *  \brief A class that represents the date range
 */
class Range
{
 public:
    QDate start;
    QDate end;
    bool isValid() const { return start.isValid() && end.isValid() && start <= end; }
    bool isSame(const Range &other) const { return start == other.start && end == other.end; }
    qint64 duration() const { return start.daysTo(end); }
    qint64 daysCount() const { return duration() + 1; }
};

#endif  // DATERANGE_H
