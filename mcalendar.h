#ifndef MCALENDAR_H
#define MCALENDAR_H

#include <QWidget>
#include "daterange.h"
#include "timerange.h"
#include <type_traits>
#include <utility>

class QLabel;
class QVBoxLayout;
class QStackedWidget;
class EditTimeDialog;
class QFrame;

class MDayView : public QWidget
{
    Q_OBJECT
 public:
    MDayView() = default;
    virtual ~MDayView() = default;
    const QDate &date() const;
    void setDate(const QDate &date);

 protected:
    virtual void onDateChanged() = 0;

 private:
    QDate m_date;
};

class MDayFactory
{
 public:
    virtual MDayView *build() const = 0;
};

template <class T, class FactoryT>
class MGenericFactory : public FactoryT
{
    using ReturnTPtr = decltype(std::declval<FactoryT>().build());
    using ReturnT = typename std::remove_pointer<ReturnTPtr>::type;

    static_assert (std::is_base_of<ReturnT, T>::value,
        "Provided T Type does not inherit type returned by Factory build method");
    virtual ReturnTPtr build() const override {
        return new T();
    }

};

template <class DayT>
class MGenericDayFactory : public MDayFactory
{
public:
    virtual MDayView * build() const override {
        return new DayT();
    }
};

class MSimpleDay : public MDayView
{
 public:
    MSimpleDay();
    void onDateChanged() override;

 private:
    QLabel *m_label;
};

using MSimpleDayFactory = MGenericFactory<MSimpleDay, MDayFactory>;



class MSimpleHeader: public QWidget
{
public:
    MSimpleHeader(QWidget *parent);

private:
    QLabel *prepareLabel(const QString &text);
};

class MRowView : public QWidget
{
 public:
    MRowView(int numberOfDays);
    virtual ~MRowView() = default;
    int daysCount() const;
    const QVector<MDayView *> &dayViews() const;
    void setFirstDate(const QDate &firstDate, const QDate &lastDate);
    void setDayFactory(MDayFactory *factory);

 protected:
    virtual void onDateChanged() = 0;
    void setDaysLayout(QLayout *layout);

 private:
    void updateDayViews();
    MDayFactory *m_factory{};
    QLayout *m_daysLayout{};
    QVector<MDayView *> m_days;
    QDate m_start;
    QDate m_end;
    int m_daysCount;
};

class MWeekRow : public MRowView
{
 public:
    MWeekRow();
    void onDateChanged() override;

 private:
    const int m_spacing = 2;
};

class MRowFactory
{
 public:
    virtual MRowView *build() const = 0;
    int daysInRow() const;
};

using MWeekRowFactory = MGenericFactory<MWeekRow, MRowFactory>;

class MCalendar : public QWidget
{
    Q_OBJECT
 public:
    explicit MCalendar(QWidget *parent = nullptr);
    void setHeader(QWidget *header);
    const QWidget *header() const;
    void setDayFactory(MDayFactory *factory);
    void setRowFactory(MRowFactory *factory);
    void setDateRange(const MDateRange &range);
    void setMonth(const QDate &month);
    const QVector<MDayView *> &dayViews() const;

    void setBackgroundColor(const QColor& color);

protected:
    virtual void onRowAdded(const MRowView *row);
    QVector<MDayView *> m_days;
    MDateRange m_range;

 private:
    void updateRows();
    QDate nextMonday(const QDate &date);
    QVector<MRowView *> m_rows;
    MSimpleDayFactory m_defaultDayFactory;
    MWeekRowFactory m_defaultRowFactory;
    MDayFactory *m_dayFactory{&m_defaultDayFactory};
    MRowFactory *m_rowFactory{&m_defaultRowFactory};
    QVBoxLayout *m_mainLayout;
    QVBoxLayout *m_rowsLayout;
    QWidget *m_header{};

    const int m_rowsVerticalMargin = 11;
    const int m_rowsHorizontalMargin = 7;

    const int m_rowSpacing = 5;
};

#endif  // MCALENDAR_H
