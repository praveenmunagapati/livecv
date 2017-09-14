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

#ifndef QPLUGINTYPESTEST_HPP
#define QPLUGINTYPESTEST_HPP

#include <QObject>
#include "qtestrunner.h"

class QPluginTypesTest : public QObject{

    Q_OBJECT
    Q_TEST_RUNNER_SUITE

public:
    QPluginTypesTest(QObject* parent = 0);
    ~QPluginTypesTest();

    QString filePath(const QString& relativePath);
    QByteArray readFile(const QString& path);

private slots:
    void initTestCase();
    void getTypesFromEngine();
};

#endif // QPLUGINTYPESTEST_HPP
