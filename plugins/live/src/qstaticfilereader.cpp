#include "qstaticfilereader.h"
#include "qfilereader.h"
#include "qstaticcontainer.h"

#include <QJSValue>

QStaticFileReader::QStaticFileReader(QQuickItem *parent)
    : QQuickItem(parent)
    , m_reader(0)
{
}

QStaticFileReader::~QStaticFileReader(){
}

void QStaticFileReader::componentComplete(){
    QQuickItem::componentComplete();
    emit init();
}

void QStaticFileReader::staticLoad(const QString &file, const QJSValue &params){
    bool monitor = false;
    if ( params.isObject() ){
        if ( params.hasOwnProperty("monitor") ){
            monitor = params.property("monitor").toBool();
        }
    }

    if ( m_reader )
        disconnect(m_reader, SIGNAL(dataChanged(QByteArray)), this, SLOT(readerDataChanged(QByteArray)));

    QStaticContainer* container = QStaticContainer::grabFromContext(this);
    m_reader = container->get<QFileReader>(file);

    if ( !m_reader ){
        m_reader = new QFileReader();
        m_reader->setSource(file);
        m_reader->componentComplete();
        container->set<QFileReader>(file, m_reader);
        connect(m_reader, SIGNAL(dataChanged(QByteArray)), this, SLOT(readerDataChanged(QByteArray)));
    }

    m_data = m_reader->data();
    emit dataChanged(m_data);

    m_reader->setMonitor(monitor);
}

void QStaticFileReader::readerDataChanged(const QByteArray &data){
    m_data = data;
    emit dataChanged(m_data);
}
