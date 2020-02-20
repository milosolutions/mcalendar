#include "mcalendar.h"
#include <QBoxLayout>
#include <QDate>
#include <QLabel>
#include <QStyleOption>

/*!
 * \class MDayView
 * \brief interface of widget representing day in MCalendat
 */

const QDate& MDayView::date() const
{
    return m_date;
}

void MDayView::setDate(const QDate& date)
{
    if (date != m_date) {
        m_date = date;
        onDateChanged();
    }
}

MSimpleDay::MSimpleDay() : MDayView()
{
    auto layout = new QVBoxLayout(this);
    m_label = new QLabel;
    m_label->setFixedWidth(50);
    layout->addWidget(m_label);
}

void MSimpleDay::onDateChanged()
{
    m_label->setText(date().toString("d"));
}


/*!
 * \class MRowView
 * \brief represents row in MCalendar
 *
 * Each subclass should call setDaysLayout method, preferably in its c-tor.
 */

MRowView::MRowView(int numberOfDays) : QWidget(), m_daysCount(numberOfDays)
{
    setObjectName("lightGrayBackgroundWidget");
}

int MRowView::daysCount() const
{
    return m_daysCount;
}

const QVector<MDayView*>& MRowView::dayViews() const
{
    return m_days;
}

void MRowView::setFirstDate(const QDate& firstDate, const QDate& lastDate)
{
    if (!firstDate.isValid()) return;
    m_start = firstDate;
    m_end = lastDate;
    updateDayViews();
}

void MRowView::setDayFactory(MDayFactory* factory)
{
    Q_ASSERT(m_daysLayout);
    Q_ASSERT_X(m_daysLayout->count() == 0, "MRowView", "Cant change factory once its already used");
    m_factory = factory;

    // prepare views - its fixed amount
    Q_ASSERT(m_daysCount > 0);

    for (int i = 0; i < m_daysCount; ++i) {
        auto dayView = m_factory->build();
        m_daysLayout->addWidget(dayView);
        m_days.append(dayView);
    }
}

/*!
 * \brief inform which layout holds day views
 * \param layout owned by MRowView subclass
 *
 * Call this method in c-tor to inform MRowView
 * which layout has day views. Layout should be empty
 * and all widgets will be added / removed automatically.
 */
void MRowView::setDaysLayout(QLayout* layout)
{
    Q_ASSERT(layout);
    Q_ASSERT_X(layout->count() == 0, "MRowView", "Layout for days should be empty");
    m_daysLayout = layout;
}

void MRowView::updateDayViews()
{
    Q_ASSERT_X(m_daysLayout, "MRowView", "Did you call setDaysLayout in your subclass?");
    Q_ASSERT_X(m_factory, "MRowView", "Day factory must be set");

    for (int i = 0; i < m_days.count(); ++i) {
        m_days.at(i)->setDate(QDate());
        m_days.at(i)->hide();
    }

    if (m_start.dayOfWeek() == 1)
        layout()->setAlignment(Qt::AlignLeft);
    else
        layout()->setAlignment(Qt::AlignRight);

    int count = m_start.daysTo(m_end) + 1;
    Q_ASSERT(count <= m_days.count());
    for (int i = 0; i < count; ++i) {
        auto view = m_days.at(i);
        view->setDate(m_start.addDays(i));
        view->show();
    }
}

MWeekRow::MWeekRow() : MRowView(7)
{
    auto layout = new QHBoxLayout(this);
    layout->setAlignment(Qt::AlignLeft);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(m_spacing);
    setDaysLayout(layout);
}

void MWeekRow::onDateChanged()
{
    // Nothing
}

int MRowFactory::daysInRow() const
{
    auto view = build();
    int count = view->daysCount();
    delete view;
    return count;
}



MSimpleHeader::MSimpleHeader(QWidget *parent) : QWidget(parent)
{
    auto mainLayout = new QHBoxLayout(this);
    mainLayout->setAlignment(Qt::AlignLeft);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(3);
    for (int i = 1; i <= 7; ++i)
        mainLayout->addWidget(
            prepareLabel(QLocale(QLocale::English).dayName(i, QLocale::ShortFormat)));
    setAutoFillBackground(true);
}

QLabel *MSimpleHeader::prepareLabel(const QString &text)
{
    auto label = new QLabel(text);
    label->setContentsMargins(0, 0, 0, 10);
    label->setFixedWidth(50);
    label->setAlignment(Qt::AlignCenter);
    return label;
}


/*!
 * \class MCalendar
 * \brief calendar widget with fully customizable delegate for day and calendar row
 */

void MCalendar::setBackgroundColor(const QColor& color)
{
    // https://wiki.qt.io/How_to_Change_the_Background_Color_of_QWidget
    QPalette pal = palette();
    pal.setColor(QPalette::Window, color);
    setAutoFillBackground(true);
    setPalette(pal);
}

MCalendar::MCalendar(QWidget* parent) : QWidget(parent)
{
    setBackgroundColor(QColor("#F7F7F7"));

    m_mainLayout = new QVBoxLayout(this);
    m_mainLayout->setAlignment(Qt::AlignTop);
    m_rowsLayout = new QVBoxLayout();
    m_mainLayout->setContentsMargins(0, 0, 0, 0);
    m_mainLayout->setSpacing(0);
    m_rowsLayout->setContentsMargins(m_rowsHorizontalMargin, m_rowsVerticalMargin,
                                     m_rowsHorizontalMargin, m_rowsVerticalMargin);
    m_rowsLayout->setSpacing(m_rowSpacing);
    m_mainLayout->addLayout(m_rowsLayout);

    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
}

void MCalendar::setHeader(QWidget* header)
{
    Q_ASSERT(header);
    if (m_header) {
        delete m_header;
    }

    m_header = header;
    m_mainLayout->insertWidget(0, m_header);
}

const QWidget* MCalendar::header() const
{
    return m_header;
}

void MCalendar::setDayFactory(MDayFactory* factory)
{
    Q_ASSERT(factory);
    Q_ASSERT_X(m_rowsLayout->count() == 0, "MCalendar",
               "Cant change factory once its already used");
    m_dayFactory = factory;
}

void MCalendar::setRowFactory(MRowFactory* factory)
{
    Q_ASSERT(factory);
    Q_ASSERT_X(m_rowsLayout->count() == 0, "MCalendar",
               "Cant change factory once its already used");
    m_rowFactory = factory;
}

void MCalendar::setDateRange(const MDateRange &range)
{
    if (!range.isValid()) return;
    if (range == m_range) return;

    m_range = range;
    updateRows();
}

void MCalendar::setMonth(const QDate& month)
{
    MDateRange range;
    range.from = QDate(month.year(), month.month(), 1);
    range.to = QDate(month.year(), month.month(), month.daysInMonth());
    setDateRange(range);
}

const QVector<MDayView*>& MCalendar::dayViews() const
{
    return m_days;
}

void MCalendar::onRowAdded(const MRowView*)
{
    // Nothing
}

void MCalendar::updateRows()
{
    if (!m_range.isValid()) return;

    // view adder
    auto addViews = [this](int n) {
        while (--n >= 0) {
            auto rowView = m_rowFactory->build();
            rowView->setDayFactory(m_dayFactory);
            m_rowsLayout->addWidget(rowView);
            m_rows.append(rowView);
            onRowAdded(rowView);
            m_days.append(rowView->dayViews());
        }
    };
    // view remover - remove first n rows
    auto removeViews = [this](int n, int daysPerRow) {
        int counter{n + 1};
        while (--counter) {
            auto item = m_rowsLayout->takeAt(0);
            delete item->widget();
            delete item;
        }
        // remove from m_rows
        m_rows.erase(m_rows.begin(), m_rows.begin() + n);
        // remove corresponding day views
        m_days.erase(m_days.begin(), m_days.begin() + n * daysPerRow);
    };

    // compute number of rows
    int daysPerRow = m_rowFactory->daysInRow();
    int daysCount = m_range.daysCount();
    daysCount += m_range.from.dayOfWeek() - 1;
    int rowsCount = daysCount / daysPerRow;
    if (daysCount - rowsCount * daysPerRow > 0) rowsCount++;

    // adjust number of row objects
    int diff = rowsCount - m_rowsLayout->count();

    if (diff < 0) removeViews(-diff, daysPerRow);  // delete extra views
    if (diff > 0) addViews(diff);                  // add missing views

    // set dates rows
    auto start = m_range.from;
    auto end = nextMonday(start).addDays(-1);
    Q_ASSERT(m_rows.count() == rowsCount && rowsCount > 0);
    m_rows.at(0)->setFirstDate(start, end);
    for (int i = 1; i < m_rows.count(); ++i) {
        auto rowView = m_rows.at(i);
        start = nextMonday(start);
        auto end = qMin(start.addDays(daysPerRow - 1), m_range.to);
        rowView->setFirstDate(start, end);
    }
}

QDate MCalendar::nextMonday(const QDate& date)
{
    return date.addDays(8 - date.dayOfWeek());
}
