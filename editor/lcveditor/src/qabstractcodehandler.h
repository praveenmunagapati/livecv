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

#ifndef QABSTRACTCODEHANDLER_H
#define QABSTRACTCODEHANDLER_H

#include <QObject>
#include "live/qlcveditorglobal.h"
#include "live/qcodecompletionmodel.h"
#include "qcodedeclaration.h"

class QTextDocument;
class QTextCursor;
class QTextBlock;

namespace lcv{

class QDocumentHandlerState;
class QDocumentEditFragment;
class QProjectDocument;
class QCodeRuntimeBinding;
class QCodeConverter;

class Q_LCVEDITOR_EXPORT QAbstractCodeHandler : public QObject{

    Q_OBJECT

public:
    explicit QAbstractCodeHandler(QObject* parent = 0);
    virtual ~QAbstractCodeHandler();

    virtual void setTarget(QTextDocument* target, QDocumentHandlerState* state) = 0;
    virtual void assistCompletion(
        const QTextCursor& cursor,
        const QChar& insertion,
        bool manuallyTriggered,
        QCodeCompletionModel* model,
        QTextCursor& cursorChange
    ) = 0;
    virtual void setDocument(QProjectDocument* document) = 0;
    virtual void updateScope(const QString& data) = 0;
    virtual void rehighlightBlock(const QTextBlock &block) = 0;
    virtual QList<QCodeDeclaration::Ptr> getDeclarations(const QTextCursor& cursor) = 0;
    virtual bool findPropertyValue(int position, int length, int& valuePosition, int& valueEnd) = 0;
    virtual void connectBindings(QList<QCodeRuntimeBinding*> bindings, QObject* root) = 0;
    virtual QDocumentEditFragment* createInjectionChannel(
        QCodeDeclaration::Ptr property,
        QObject* runtime,
        QCodeConverter* converter
    ) = 0;
};

}// namespace

#endif // QABSTRACTCODEHANDLER_H
