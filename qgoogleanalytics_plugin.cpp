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

#include "qgoogleanalytics_plugin.h"
#include "qgoogleanalytics.h"

#include <qqml.h>

void QGoogleAnalyticsPlugin::registerTypes(const char *uri)
{
    // @uri Indev.net.br.qgoogleanalytics
    qmlRegisterType<QGoogleAnalytics>(uri, 1, 0, "QGoogleAnalytics");
}

