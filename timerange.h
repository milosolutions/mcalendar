#ifndef MTIMERANGE_H
#define MTIMERANGE_H

#include <QTime>

/*! \class MTimeRange
 *  \brief A class that represents the time range
 */
class MTimeRange
{
 public:
    QTime from;
    QTime to;

    MTimeRange() {}
    MTimeRange(const QTime &from, const QTime &to)
    {
        this->from = from;
        this->to = to;
    }

    qint64 durationInSeconds() const { 
        return this->from.secsTo(to); 
    }
    
    bool equals(const MTimeRange &other) const { 
        return this->from == other.from && this->to == other.to; 
    }
    bool operator==(const MTimeRange &other) const {
        return this->equals(other);
    }
};

#endif  // TIMERANGE_H
