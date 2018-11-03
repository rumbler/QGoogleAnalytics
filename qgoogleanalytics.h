/*************************************************************************
 *                                                                       *
 *  Copyright (C) 2014-2018  Rumbler N. Soppa                            *
 *                                                                       *
 *   Este programa é software livre; você pode redistribuí-lo e/ou       *
 *   modificá-lo sob os termos da Licença Pública Geral GNU, conforme    *
 *   publicada pela Free Software Foundation; tanto a versão 2 da        *
 *   Licença como (a seu critério) qualquer versão mais nova.            *
 *                                                                       *
 *   Este programa é distribuído na expectativa de ser útil, mas SEM     *
 *   QUALQUER GARANTIA; sem mesmo a garantia implícita de                *
 *   COMERCIALIZAÇÃO ou de ADEQUAÇÃO A QUALQUER PROPÓSITO EM             *
 *   PARTICULAR. Consulte a Licença Pública Geral GNU para obter mais    *
 *   detalhes.                                                           *
 *                                                                       *
 *   Você deve ter recebido uma cópia da Licença Pública Geral GNU       *
 *   junto com este programa; se não, escreva para a Free Software       *
 *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA            *
 *   02111-1307, USA.                                                    *
 *                                                                       *
 *************************************************************************/

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
    QByteArray userAgent;
    bool m_enabled;
    QSettings *st;

    // metods privates
private:
    void setValue(const QString &obj, const QVariant &vl);

    QVariant getValue(const QString &obj);
};

#endif // QGOOGLEANALYTICS_H
