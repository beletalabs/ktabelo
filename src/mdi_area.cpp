/*
    SPDX-FileCopyrightText: 2022 naracanto https://naracanto.github.io

    SPDX-License-Identifier: GPL-3.0-or-later
*/

#include "mdi_area.h"

#include <QMdiSubWindow>
#include <QUrl>

#include "mdi_document.h"


MdiArea::MdiArea(QWidget *parent)
    : QMdiArea(parent)
{

}


QMdiSubWindow *MdiArea::findSubWindow(const QUrl &url) const
{
    if (url.isEmpty())
        return nullptr;

    const QList<QMdiSubWindow *> subWindows = subWindowList();
    for (auto *subWindow : subWindows) {

        auto *document = qobject_cast<MdiDocument *>(subWindow->widget());
        if (document->url() == url)
            return subWindow;
    }

    return nullptr;
}


void MdiArea::updateSubWindowTitle(MdiDocument *document)
{
    if (!document)
        return;

    if (!document->filenameSequenceNumber())
        document->setFilenameSequenceNumber(latestFilenameSequenceNumber(document->url()) + 1);
}


int MdiArea::latestFilenameSequenceNumber(const QUrl &url) const
{
    int number = 0;

    const QList<QMdiSubWindow *> subWindows = subWindowList();
    for (auto *subWindow : subWindows) {

        auto *document = qobject_cast<MdiDocument *>(subWindow->widget());
        if (document->url().fileName() == url.fileName())
            if (document->filenameSequenceNumber() > number)
                number = document->filenameSequenceNumber();
    }

    return number;
}
