#include "notecomments.h"
#include "notecomments_p.h"

#include <QDebug>

#include "share/wizobject.h"
#include "sync/token.h"
#include "sync/apientry.h"
#include "icore.h"

using namespace Core;

namespace WizService {
namespace Internal {

static NoteCommentsPrivate* m_comments = 0;

NoteCommentsPrivate::NoteCommentsPrivate()
{
    connect(ICore::instance(), SIGNAL(viewNoteLoaded(CWizDocumentView*, const WIZDOCUMENTDATA&)),
            SLOT(onViewNoteLoaded(CWizDocumentView*, const WIZDOCUMENTDATA&)));
    connect(Token::instance(), SIGNAL(tokenAcquired(QString,QString)), SLOT(onTokenAcquired(QString, QString)));
}

NoteCommentsPrivate::~NoteCommentsPrivate()
{
    m_comments = 0;
}

void NoteCommentsPrivate::onViewNoteLoaded(CWizDocumentView* view, const WIZDOCUMENTDATA& note)
{
    //m_map.insert(view, note);

    //Token::requestToken();
}

void NoteCommentsPrivate::onTokenAcquired(const QString& strToken, const QString& strMsg)
{
    Q_UNUSED(strMsg);

    if (strToken.isEmpty())
        return;

    loadComments(strToken);
}

void NoteCommentsPrivate::onCommentsButtonClicked()
{
}

void NoteCommentsPrivate::loadComments(const QString& strToken)
{
    QMap<CWizDocumentView*, WIZDOCUMENTDATA>::const_iterator it;
    for (it = m_map.begin(); it != m_map.end(); it++) {
        qDebug() << ApiEntry::commentUrl(strToken, it.value().strKbGUID, it.value().strGUID);
    }
}


} // namespace Internal


NoteComments::NoteComments()
{
}

void NoteComments::init()
{
    if (!Internal::m_comments) {
        Internal::m_comments = new Internal::NoteCommentsPrivate();
    }
}


} // namespace WizService