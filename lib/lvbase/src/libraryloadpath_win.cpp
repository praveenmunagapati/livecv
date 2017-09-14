
#include "live/libraryloadpath.h"
#include "Windows.h"

#include <QDir>
#include <QDirIterator>
#include <QFile>
#include <QDebug>

//TODO: Use vlog
//#define QLIBRARY_LOAD_PATH_DEBUG_FLAG
#ifdef QLIBRARY_LOAD_PATH_DEBUG_FLAG
#define QLIBRARY_LOAD_PATH_DEBUG(_param) qDebug() << "LIBRARY PATH:" << (_param)
#else
#define QLIBRARY_LOAD_PATH_DEBUG(_param)
#endif


namespace lcv{

// SetDefaultDllDirectories(
//   LOAD_LIBRARY_SEARCH_APPLICATION_DIR |
//   LOAD_LIBRARY_SEARCH_SYSTEM32 |
//   LOAD_LIBRARY_SEARCH_USER_DIRS
// )
// and AddDllDirectory() have weird behaviors when loading QtQuick.Controls, it's why we prefer to
// manipulate the 'PATH' environment variable instead.

namespace {

QByteArray pathContents;

}// namespace

void LibraryLoadPath::addImpl(const QString& path, const QString& , bool recursive){
    bool firstRun = false;

    if ( pathContents.isEmpty() ){
        firstRun = true;
        pathContents = qgetenv("PATH");
    }

    QDirIterator dit(path);
    while ( dit.hasNext() ){
        dit.next();
        QFileInfo info = dit.fileInfo();
        if ( info.fileName() == "." || info.fileName() == ".." )
            continue;

        if ( info.isDir() ){
            QString filePath = info.filePath();
            filePath.replace('/', '\\');
            pathContents += ";" + filePath.toUtf8();
            QLIBRARY_LOAD_PATH_DEBUG("Added path \'" + filePath + "\'");
            if ( recursive )
                addImpl(info.filePath(), "", recursive);
        }
    }

    if ( firstRun ){
        SetEnvironmentVariableA("PATH", pathContents.data());
    }
}

}// namespace
