#ifndef RANDOMNUMBERGENERATOR_H
#define RANDOMNUMBERGENERATOR_H

#include <QObject>
#include <QTimer>
#include <QRandomGenerator>

class RandomNumberGenerator : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int number READ number NOTIFY numberChanged)
    Q_PROPERTY(int min READ min WRITE setMin NOTIFY minChanged)
    Q_PROPERTY(int max READ max WRITE setMax NOTIFY maxChanged)
    Q_PROPERTY(int interval READ interval WRITE setInterval NOTIFY intervalChanged)

public:
    explicit RandomNumberGenerator(QObject *parent = nullptr);

    int number() const;
    int min() const;
    int max() const;
    int interval() const;

    Q_INVOKABLE void setMin(int min);
    Q_INVOKABLE void setMax(int max);
    Q_INVOKABLE void setInterval(int interval);

public slots:
    void start(int interval);

signals:
    void numberChanged(int number);
    void minChanged(int min);
    void maxChanged(int max);
    void intervalChanged(int interval);

private:
    void generateNumber();

    QTimer m_timer;
    int m_number;
    int m_min;
    int m_max;
    int m_interval;
};

#endif // RANDOMNUMBERGENERATOR_H
