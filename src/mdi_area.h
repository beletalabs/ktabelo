/*
    SPDX-FileCopyrightText: 2022 naracanto https://naracanto.github.io

    SPDX-License-Identifier: GPL-3.0-or-later
*/

#ifndef MDI_AREA_H
#define MDI_AREA_H

#include <QMdiArea>

class QMdiSubWindow;
class QUrl;

class MdiDocument;


class MdiArea : public QMdiArea
{
    Q_OBJECT

public:
    explicit MdiArea(QWidget *parent = nullptr);

    QMdiSubWindow *findSubWindow(const QUrl &url) const;

    void closeOtherSubWindows(QMdiSubWindow *givenSubWindow = nullptr);

public Q_SLOTS:
    void updateSubWindowTitle(MdiDocument *document);

private:
    int latestFilenameSequenceNumber(const QUrl &url) const;
};

#endif // MDI_AREA_H
