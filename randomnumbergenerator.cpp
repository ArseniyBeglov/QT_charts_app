#include "randomnumbergenerator.h"

RandomNumberGenerator::RandomNumberGenerator(QObject *parent)
    : QObject(parent), m_number(0), m_min(0), m_max(100), m_interval(1000)
{
    connect(&m_timer, &QTimer::timeout, this, &RandomNumberGenerator::generateNumber);
}

int RandomNumberGenerator::number() const
{
    return m_number;
}

int RandomNumberGenerator::min() const
{
    return m_min;
}

int RandomNumberGenerator::max() const
{
    return m_max;
}

int RandomNumberGenerator::interval() const
{
    return m_interval;
}

void RandomNumberGenerator::setMin(int min)
{
    if (m_min != min) {
        m_min = min;
        emit minChanged(m_min);
    }
}

void RandomNumberGenerator::setMax(int max)
{
    if (m_max != max) {
        m_max = max;
        emit maxChanged(m_max);
    }
}

void RandomNumberGenerator::setInterval(int interval)
{
    if (m_interval != interval) {
        m_interval = interval;
        emit intervalChanged(m_interval);
    }
}

void RandomNumberGenerator::start(int interval)
{
    setInterval(interval);
    m_timer.start(m_interval);
}

void RandomNumberGenerator::generateNumber()
{
    m_number = QRandomGenerator::global()->bounded(m_min, m_max + 1);
    emit numberChanged(m_number);
}
