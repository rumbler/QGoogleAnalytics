#include "qgoogleanalytics.h"
#include <QUuid>
#include <QDir>
#include <QHostInfo>
#include <QNetworkRequest>
#include <QUrlQuery>
#include <QNetworkAccessManager>
#include <QSysInfo>

QGoogleAnalytics::QGoogleAnalytics(QObject *parent):
    QObject(parent)
{
    st = new QSettings(QDir::homePath() + "/.config/" +
                      APP_ORG_DOMAIN + "/" +
                      APP_NAME + ".conf",
                      QSettings::IniFormat, this);

    if(getValue("App/uuid").value<QString>().isEmpty())
        setValue("App/uuid", QUuid::createUuid().toString());

    m_uuid = getValue("App/uuid").value<QString>();

#ifdef Q_OS_LINUX
    userAgent.append(QString("Mozilla/5.0 (X11; Linux x86_64) Gecko/20100101 Firefox/15.0.1"));
#endif

#ifdef Q_OS_MACOS
    userAgent.append(QString("Mozilla/5.0 (Macintosh; Intel Mac OS X %1) AppleWebKit/601.3.9 "
                             "(KHTML, like Gecko) Version/9.0.2 Safari/601.3.9")
                     .arg(QSysInfo::productVersion()));
#endif

#ifdef Q_OS_WIN
    userAgent.append(QString("Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 "
                             "(KHTML, like Gecko) Chrome/42.0.2311.135 Safari/537.36 Edge/12.246"));
#endif

}

QGoogleAnalytics::~QGoogleAnalytics()
{

}

void QGoogleAnalytics::logScreen(const QString &pageTitle)
{
    if(!m_enabled)
        return;

    // prepare request
    QNetworkRequest req(QUrl("https://google-analytics.com/collect"));
    req.setRawHeader("User-Agent", userAgent);
    req.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    // prepare query
    QUrlQuery query;
    query.addQueryItem("v", "1");               // version protocol
    query.addQueryItem("tid", m_tid);           // tracking id
    query.addQueryItem("cid", m_uuid);          // user id
    query.addQueryItem("an", APP_NAME);         // application name
    query.addQueryItem("aid", APP_ORG_DOMAIN);  // application id
    query.addQueryItem("av", APP_VERSION);      // application version
    query.addQueryItem("t", "pageview");        // HIT type
    query.addQueryItem("dp", "/" + pageTitle);  //
    query.addQueryItem("dt", pageTitle);        //
    query.addQueryItem("cd", pageTitle);        // screen name

    // prepare data
    QByteArray data;
    data.append(query.query());

    // sending data
    QNetworkAccessManager *net = new QNetworkAccessManager;
    net->post(req, data);
}

void QGoogleAnalytics::logEvent(const QString &eventCategory,
                                const QString &eventAction)
{
    if(!m_enabled)
        return;

    // prepare request
    QNetworkRequest req(QUrl("https://google-analytics.com/collect"));
    req.setRawHeader("User-Agent", userAgent);
    req.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    // prepare query
    QUrlQuery query;
    query.addQueryItem("v", "1");               // version protocol
    query.addQueryItem("tid", m_tid);           // tracking id
    query.addQueryItem("cid", m_uuid);          // user id
    query.addQueryItem("an", APP_NAME);         // application name
    query.addQueryItem("aid", APP_ORG_DOMAIN);  // application id
    query.addQueryItem("av", APP_VERSION);      // application version
    query.addQueryItem("t", "event");           // HIT type
    query.addQueryItem("ec", eventCategory);    // event category
    query.addQueryItem("ea", eventAction);      // action event

    // prepare data
    QByteArray data;
    data.append(query.query());

    // sending data
    QNetworkAccessManager *net = new QNetworkAccessManager;
    net->post(req, data);
}

void QGoogleAnalytics::logException(const QString &description,
                                    const bool fatal)
{
    if(!m_enabled)
        return;

    // prepare request
    QNetworkRequest req(QUrl("https://google-analytics.com/collect"));
    req.setRawHeader("User-Agent", userAgent);
    req.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    // prepare query
    QUrlQuery query;
    query.addQueryItem("v", "1");               // version protocol
    query.addQueryItem("tid", m_tid);           // tracking id
    query.addQueryItem("cid", m_uuid);          // user id
    query.addQueryItem("an", APP_NAME);         // application name
    query.addQueryItem("aid", APP_ORG_DOMAIN);  // application id
    query.addQueryItem("av", APP_VERSION);      // application version
    query.addQueryItem("t", "exception");       // HIT type
    query.addQueryItem("exd", description);     // except desciption

    // except is fatal
    if(fatal)
        query.addQueryItem("exf", "1");         // except is fatal? true
    else
        query.addQueryItem("exf", "0");         // except is fatal? false

    // prepare data
    QByteArray data;
    data.append(query.query());

    // sending data
    QNetworkAccessManager *net = new QNetworkAccessManager;
    net->post(req, data);
}

QString QGoogleAnalytics::tid() const
{
    return m_tid;
}

bool QGoogleAnalytics::enabled() const
{
    return m_enabled;
}

void QGoogleAnalytics::tid(QString tid)
{
    m_tid = tid;
}

void QGoogleAnalytics::setEnabled(bool enabled)
{
    if (m_enabled == enabled)
        return;

    m_enabled = enabled;
    emit enabledChanged(m_enabled);
}

void QGoogleAnalytics::setValue(const QString &obj, const QVariant &vl)
{
    st->setValue( obj, vl); // set value on object
}

QVariant QGoogleAnalytics::getValue(const QString &obj)
{
    return st->value(obj); // get value for object
}

