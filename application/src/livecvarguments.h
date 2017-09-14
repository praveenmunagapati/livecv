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

#ifndef QLIVECVARGUMENTS_H
#define QLIVECVARGUMENTS_H

#include <QObject>

namespace lcv{

class CommandLineParser;
class LiveCVArguments{

public:
    explicit LiveCVArguments(const QString& header, int argc, const char* const argv[]);
    ~LiveCVArguments();

    bool previewFlag() const;
    bool consoleFlag() const;
    bool fileLogFlag() const;

    bool pluginInfoFlag() const;
    const QString& pluginInfoImport() const;

    bool helpFlag() const;
    bool versionFlag() const;
    QString helpString() const;

    const QStringList& monitoredFiles() const;

    CommandLineParser* parser();

    const QString& script() const;
    const QStringList& scriptArguments() const;

private:
    void initialize(int argc, const char* const argv[]);

    CommandLineParser* m_parser;

    bool m_fileLogFlag;
    bool m_consoleFlag;
    bool m_previewFlag;

    bool m_pluginInfoFlag;
    QString m_pluginInfoImport;

    QStringList m_monitoredFiles;

};

inline bool LiveCVArguments::previewFlag() const{
    return m_previewFlag;
}

inline bool LiveCVArguments::consoleFlag() const{
    return m_consoleFlag;
}

inline bool LiveCVArguments::fileLogFlag() const{
    return m_fileLogFlag;
}

inline const QString &LiveCVArguments::pluginInfoImport() const{
    return m_pluginInfoImport;
}

inline const QStringList &LiveCVArguments::monitoredFiles() const{
    return m_monitoredFiles;
}

inline CommandLineParser *LiveCVArguments::parser(){
    return m_parser;
}


}// namespace

#endif // QLIVECVARGUMENTS_H
