#ifndef QGOOGLEANALYTICS_H
#define QGOOGLEANALYTICS_H

#include <QQuickItem>
#include <QObject>
#include <QSettings>

class QGoogleAnalytics : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(QGoogleAnalytics)

    Q_PROPERTY(QString tid READ tid WRITE tid)
    Q_PROPERTY(bool enabled READ enabled WRITE setEnabled NOTIFY enabledChanged)

public:
    QGoogleAnalytics(QObject *parent = nullptr);
    ~QGoogleAnalytics();

    Q_INVOKABLE void logScreen(const QString &pageTitle);
    Q_INVOKABLE void logEvent(const QString &eventCategory,
                              const QString &eventAction);
    Q_INVOKABLE void logException(const QString &description,
                                  const bool fatal = false);
    QString tid() const;
    bool enabled() const;

public slots:
    void tid(QString tid);
    void setEnabled(bool enabled);

signals:
    void enabledChanged(bool enabled);

private:
    const QString APP_NAME = QCoreApplication::applicationName();
    const QString APP_ORG_DOMAIN = QCoreApplication::organizationDomain();
    const QString APP_VERSION = QCoreApplication::applicationVersion();
    QString m_uuid;
    QString m_tid;
    bool m_enabled;
    QSettings *st;

    // metods privates
private:
    void setValue(const QString &obj, const QVariant &vl);

    QVariant getValue(const QString &obj);
};

#endif // QGOOGLEANALYTICS_H
