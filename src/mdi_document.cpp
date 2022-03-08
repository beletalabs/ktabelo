/*
    SPDX-FileCopyrightText: 2022 naracanto https://naracanto.github.io

    SPDX-License-Identifier: GPL-3.0-or-later
*/

#include "mdi_document.h"

#include <QDebug>

#include <KLocalizedString>


MdiDocument::MdiDocument(QWidget *parent)
    : TabularDocument(parent)
    , m_url{QUrl()}
    , m_filenameSequenceNumber{0}
    , m_pathVisibleInWindowTitle{false}
    , m_modified{false}
{

}


void MdiDocument::setUrl(const QUrl &url)
{
    if (url != m_url) {
        bool update = true;

        if (url.fileName() != m_url.fileName()) {
            m_filenameSequenceNumber = 0;
            update = false; // Not necessary to update the window title twice
        }

        m_url = url;
        Q_EMIT urlChanged(url);

        if (update)
            updateWindowTitle();
    }
}


QUrl MdiDocument::url() const
{
    return m_url;
}


void MdiDocument::setFilenameSequenceNumber(const int number)
{
    if (number != m_filenameSequenceNumber) {
        m_filenameSequenceNumber = number;
        Q_EMIT filenameSequenceNumberChanged(number);

        updateWindowTitle();
    }
}


int MdiDocument::filenameSequenceNumber() const
{
    return m_filenameSequenceNumber;
}


void MdiDocument::setPathVisibleInWindowTitle(const bool visible)
{
    if (visible != m_pathVisibleInWindowTitle) {
        m_pathVisibleInWindowTitle = visible;

        updateWindowTitle();
    }
}


bool MdiDocument::isPathVisibleInWindowTitle() const
{
    return m_pathVisibleInWindowTitle;
}


void MdiDocument::setModified(const bool modified)
{
    if (modified != m_modified) {
        m_modified = modified;
        Q_EMIT modifiedChanged(modified);
    }
}


bool MdiDocument::isModified() const
{
    return m_modified;
}


void MdiDocument::updateWindowTitle()
{
    qInfo() << "  Update document window title:" << m_url.toDisplayString() << m_filenameSequenceNumber << m_pathVisibleInWindowTitle;

    QString title;

    if (!m_url.isEmpty())
        title = m_pathVisibleInWindowTitle ? m_url.toDisplayString() : m_url.fileName();
    else
        title = i18n("Untitled");

    if (m_filenameSequenceNumber > 1 && (!m_pathVisibleInWindowTitle || m_url.isEmpty()))
        title = i18n("%1 (%2)", title, m_filenameSequenceNumber);

    setWindowTitle(title);
}


bool MdiDocument::load(const QUrl &url)
{
    if (!m_url.isEmpty())
        return false;

    setUrl(url);

    return true;
}
