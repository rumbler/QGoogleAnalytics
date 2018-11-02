#include "qgoogleanalytics_plugin.h"
#include "qgoogleanalytics.h"

#include <qqml.h>

void QGoogleAnalyticsPlugin::registerTypes(const char *uri)
{
    // @uri Indev.net.br.qgoogleanalytics
    qmlRegisterType<QGoogleAnalytics>(uri, 1, 0, "QGoogleAnalytics");
}

