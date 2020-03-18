#include <QtTest>
#include <QCoreApplication>

#include <mcalendar.h>

class MCalendarTest : public QObject
{
    Q_OBJECT

public:
    MCalendarTest();
    ~MCalendarTest();

private slots:
    void testMCalendarSetHeader();
    void testMCalendarSetDateRange();
    void testMCalendarSetMonth();
    void testMDateRangeCalculations();
    void testMTimeRangeCalculations();
};

MCalendarTest::MCalendarTest()
{

}

MCalendarTest::~MCalendarTest()
{

}

void MCalendarTest::testMCalendarSetHeader()
{
    MCalendar mCalendar;
    mCalendar.setHeader(new QWidget());
    QVERIFY(mCalendar.header());
}

void MCalendarTest::testMCalendarSetDateRange()
{
    MCalendar mCalendar;
    MDateRange range;
    range.from = QDate(1900, 10, 1);
    range.to = QDate(1900, 10, 31);
    mCalendar.setDateRange(MDateRange(range));

    QVector<QDate> expectedDays;
    for (int i=1; i<=31; ++i) {
        expectedDays.append(QDate(1900, 10, i));
    }

    QVERIFY(mCalendar.dayViews().size());
    QCOMPARE(mCalendar.dayViews().size(), 35);

    for (int i=0; i<expectedDays.size(); ++i) {
        QCOMPARE(mCalendar.dayViews().at(i)->date(), expectedDays.at(i));
    }
}

void MCalendarTest::testMCalendarSetMonth()
{
    MCalendar mCalendar;
    mCalendar.setMonth(QDate(1900, 1, 1));

    QVector<QDate> expectedDays;
    for (int i=1; i<=31; ++i) {
        expectedDays.append(QDate(1900, 1, i));
    }

    QVERIFY(mCalendar.dayViews().size());
    QCOMPARE(mCalendar.dayViews().size(), 35);

    for (int i=0; i<expectedDays.size(); ++i) {
        QCOMPARE(mCalendar.dayViews().at(i)->date(), expectedDays.at(i));
    }
}

void MCalendarTest::testMDateRangeCalculations() {
    QDate from(1900, 1, 1);
    QDate to(1900, 1, 10);
    MDateRange mDateRange{from, to};
    QVERIFY(mDateRange.isValid());
    QCOMPARE(mDateRange.duration(), 9);
    QCOMPARE(mDateRange.daysCount(), 10);

    QDate otherFrom(1900, 1, 59);
    QDate otherTo(1900, 1, 63);
    MDateRange otherMDateRange{otherFrom, otherTo};

    QVERIFY(!mDateRange.equals(otherMDateRange));
}

void MCalendarTest::testMTimeRangeCalculations() {
    QTime from(0, 0, 10);
    QTime to(0, 0, 20);
    MTimeRange mTimeRange{from, to};
    QCOMPARE(mTimeRange.durationInSeconds(), 10);

    QTime otherFrom(0, 0, 10);
    QTime otherTo(0, 0, 50);
    MTimeRange otherMTimeRange{otherFrom, otherTo};
    QVERIFY(!(mTimeRange.equals(otherMTimeRange)));
}

QTEST_MAIN(MCalendarTest)

#include "tst_mcalendartest.moc"
