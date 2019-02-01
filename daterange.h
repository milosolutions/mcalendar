#ifndef MDATERANGE_H
#define MDATERANGE_H

#include <QDate>

/*! \class MDateRange
 *  \brief A class that represents the date range
 */
class MDateRange
{
 public:
    QDate from;
    QDate to;

    bool isValid() const { 
        return this->from.isValid() && 
               this->to.isValid() && 
               this->from <= this->to; 
    }
    qint64 duration() const { 
        return this->from.daysTo(to); 
    }
    qint64 daysCount() const {
         return this->duration() + 1; 
    }
    
    bool equals(const MDateRange &other) const { 
        return this->from == other.from && this->to == other.to; 
    }
    bool operator==(const MDateRange &other) const {
        return this->equals(other);
    }
};

#endif  // MDATERANGE_H
