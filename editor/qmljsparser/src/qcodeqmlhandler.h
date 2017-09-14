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

#ifndef QCODEQMLHANDLER_H
#define QCODEQMLHANDLER_H

#include "live/qqmljsparserglobal.h"
#include "live/qabstractcodehandler.h"
#include "live/qprojectdocument.h"
#include "live/qdocumentqmlscope.h"
#include "live/qprojectqmlscope.h"
#include "live/qcodedeclaration.h"
#include "live/lockedfileiosession.h"

#include <QTextCursor>

class QQmlEngine;

namespace lcv{

class QProjectQmlScanner;
class QPluginInfoExtractor;
class QQmlJsHighlighter;
class QQmlCompletionContextFinder;
class QQmlCompletionContext;
class QQmlJsSettings;

class Q_QMLJSPARSER_EXPORT QCodeQmlHandler : public QAbstractCodeHandler{

    Q_OBJECT
    Q_DISABLE_COPY(QCodeQmlHandler)

public:
    explicit QCodeQmlHandler(
        QQmlEngine* engine,
        QMutex* engineMutex,
        LockedFileIOSession::Ptr lockedFileIO,
        QObject* parent = 0
    );
    ~QCodeQmlHandler();

    void assistCompletion(
        const QTextCursor& cursor,
        const QChar& insertion,
        bool manuallyTriggered,
        QCodeCompletionModel* model,
        QTextCursor& cursorChange
    ) Q_DECL_OVERRIDE;
    void setTarget(QTextDocument *target, QDocumentHandlerState* state) Q_DECL_OVERRIDE;
    void setDocument(QProjectDocument* document) Q_DECL_OVERRIDE;
    void updateScope(const QString& data) Q_DECL_OVERRIDE;
    void rehighlightBlock(const QTextBlock& block) Q_DECL_OVERRIDE;
    QList<lcv::QCodeDeclaration::Ptr> getDeclarations(const QTextCursor& cursor) Q_DECL_OVERRIDE;
    bool findPropertyValue(int position, int length, int& valuePosition, int& valueEnd) Q_DECL_OVERRIDE;
    void connectBindings(QList<QCodeRuntimeBinding*> bindings, QObject* root) Q_DECL_OVERRIDE;
    QDocumentEditFragment* createInjectionChannel(
        QCodeDeclaration::Ptr property,
        QObject* runtime,
        QCodeConverter* converter
    ) Q_DECL_OVERRIDE;

    QPluginInfoExtractor *getPluginInfoExtractor(const QString& import);

    QQmlJsSettings* settings();

public slots:
    void newDocumentScopeReady();
    void newProjectScope();
    void newProject(const QString& path);
    void directoryChanged(const QString& path);
    void fileChanged(const QString& path);
    void loadImport(const QString& import);

private:
    void suggestionsForGlobalQmlContext(
        const QQmlCompletionContext& context,
        QList<QCodeCompletionSuggestion>& suggestions
    );

    void suggestionsForImport(
        const QQmlCompletionContext& context,
        QList<QCodeCompletionSuggestion>& suggestions
    );
    void suggestionsForStringImport(
        const QString &enteredPath,
        QList<QCodeCompletionSuggestion>& suggestions,
        QString &filter
    );
    void suggestionsForRecursiveImport(
        int index,
        const QString &dir,
        const QStringList& expression,
        QList<QCodeCompletionSuggestion>& suggestions
    );

    void suggestionsForValueObject(
        const QDocumentQmlObject& object,
        QList<QCodeCompletionSuggestion>& suggestions,
        bool extractProperties,
        bool extractFunctions,
        bool extractSlots,
        bool extractSignals
    );

    void suggestionsForNamespaceTypes(
        const QString& typeNameSpace,
        QList<QCodeCompletionSuggestion>& suggestions
    );
    void suggestionsForNamespaceImports(
        QList<QCodeCompletionSuggestion>& suggestions
    );
    void suggestionsForDocumentsIds(
        QList<QCodeCompletionSuggestion>& suggestions
    );

    void suggestionsForLeftBind(
        const QQmlCompletionContext& context,
        int cursorPosition,
        QList<QCodeCompletionSuggestion>& suggestions
    );
    void suggestionsForRightBind(
        const QQmlCompletionContext& context,
        int cursorPosition,
        QList<QCodeCompletionSuggestion>& suggestions
    );
    void suggestionsForLeftSignalBind(
        const QQmlCompletionContext& context,
        int cursorPosition,
        QList<QCodeCompletionSuggestion>& suggestions
    );

    QString extractQuotedString(const QTextCursor& cursor) const;

    QTextDocument*      m_target;
    QQmlJsHighlighter*  m_highlighter;
    QQmlJsSettings*     m_settings;
    QQmlEngine*         m_engine;
    QQmlCompletionContextFinder* m_completionContextFinder;

    QProjectDocument* m_document;


    QDocumentQmlScope::Ptr       m_documentScope;
    QProjectQmlScope::Ptr        m_projectScope;
    bool                         m_newScope;
    QProjectQmlScanner*          m_scanner;

};

inline QQmlJsSettings *QCodeQmlHandler::settings(){
    return m_settings;
}

}// namespace

#endif // QCODEQMLHANDLER_H
