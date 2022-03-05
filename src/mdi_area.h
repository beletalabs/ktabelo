/*
    SPDX-FileCopyrightText: 2022 naracanto https://naracanto.github.io

    SPDX-License-Identifier: GPL-3.0-or-later
*/

#ifndef MDI_AREA_H
#define MDI_AREA_H

#include <QMdiArea>

class QUrl;

class MdiDocument;


class MdiArea : public QMdiArea
{
    Q_OBJECT

public:
    explicit MdiArea(QWidget *parent = nullptr);

public Q_SLOTS:
    void updateSubWindowTitle(MdiDocument *document);

private:
    int latestFilenameSequenceNumber(const QUrl &url) const;
};

#endif // MDI_AREA_H
