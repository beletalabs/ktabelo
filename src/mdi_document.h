/*
    SPDX-FileCopyrightText: 2022 naracanto https://naracanto.github.io

    SPDX-License-Identifier: GPL-3.0-or-later
*/

#ifndef MDI_DOCUMENT_H
#define MDI_DOCUMENT_H

#include <QWidget>
#include <QUrl>

#include "tabular_document.h"


class MdiDocument : public TabularDocument
{
    Q_OBJECT
    Q_PROPERTY(QUrl url MEMBER m_url READ url WRITE setUrl NOTIFY urlChanged)
    Q_PROPERTY(int filenameSequenceNumber MEMBER m_filenameSequenceNumber READ filenameSequenceNumber WRITE setFilenameSequenceNumber NOTIFY filenameSequenceNumberChanged)
    Q_PROPERTY(bool pathVisibleInWindowTitle MEMBER m_pathVisibleInWindowTitle READ isPathVisibleInWindowTitle WRITE setPathVisibleInWindowTitle)

public:
    explicit MdiDocument(QWidget *parent = nullptr);

    QUrl url() const;
    int filenameSequenceNumber() const;
    bool isPathVisibleInWindowTitle() const;

public Q_SLOTS:
    void setUrl(const QUrl &url);
    void setFilenameSequenceNumber(const int number);
    void setPathVisibleInWindowTitle(const bool visible);

Q_SIGNALS:
    void urlChanged(const QUrl &url);
    void filenameSequenceNumberChanged(const int number);

private:
    void updateWindowTitle();

private:
    QUrl m_url;
    int m_filenameSequenceNumber;
    bool m_pathVisibleInWindowTitle;
};

#endif // MDI_DOCUMENT_H
