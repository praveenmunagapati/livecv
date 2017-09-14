TEMPLATE = lib
TARGET   = qmljsparser
QT      += core qml quick xml
CONFIG  += qt c++11

linkLocalLibrary(lib/lvbase, lvbase)
linkLocalLibrary(editor/lcveditor, lcveditor)

DEFINES += Q_QMLJSPARSER_LIB

win32:{
    DESTDIR    = $$DEPLOY_PATH/dev/lib
    DLLDESTDIR = $$DEPLOY_PATH
}else:DESTDIR = $$DEPLOY_PATH

#ENABLE_PLUGINTYPES = true

!isEmpty(ENABLE_PLUGINTYPES){
    message(Plugin Types Enabled: Live CV will use private libraries)
    QT += core-private qml-private quick-private
    DEFINES += Q_PLUGINTYPES_ENABLED
}

include($$PWD/src/qmljsparser.pri)
include($$PWD/3rdparty/3rdparty.pro)
include($$PWD/plugintypes/plugintypes.pri)
include($$PWD/include/qmljsparserheaders.pri)
