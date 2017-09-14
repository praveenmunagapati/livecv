/****************************************************************************
**
** Copyright (C) 2014-2017 Dinu SV.
** (contact: mail@dinusv.com)
** This file is part of Live CV Application.
**
** GNU Lesser General Public License Usage
** This file may be used under the terms of the GNU Lesser
** General Public License version 3 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPLv3 included in the
** packaging of this file. Please review the following information to
** ensure the GNU Lesser General Public License version 3 requirements
** will be met: https://www.gnu.org/licenses/lgpl.html.
**
****************************************************************************/

#include <QtGui/QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "livecv.h"
#include "livecvarguments.h"
#include "live/libraryloadpath.h"

using namespace lcv;

int main(int argc, char *argv[]){

    QGuiApplication app(argc, argv);
    QGuiApplication::setApplicationName("Live CV");
    QGuiApplication::setApplicationVersion(LiveCV::versionString());

    LiveCV::registerTypes();
    LiveCV livecv(argc, argv);

    if ( livecv.arguments()->helpFlag() ){
        printf("%s", qPrintable(livecv.arguments()->helpString()));
        return 0;
    } else if ( livecv.arguments()->versionFlag() ){
        printf("%s\n", qPrintable(livecv.versionString()));
        return 0;
    }

    LibraryLoadPath::addRecursive(livecv.dir() + "/plugins", livecv.dir() + "/link");

    if ( livecv.arguments()->pluginInfoFlag() ){
        printf("%s", livecv.extractPluginInfo(livecv.arguments()->pluginInfoImport()).data());
        return 0;
    }

    livecv.loadQml(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
