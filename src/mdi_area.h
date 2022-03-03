/*
    SPDX-FileCopyrightText: 2022 naracanto https://naracanto.github.io

    SPDX-License-Identifier: GPL-3.0-or-later
*/

#ifndef MDI_AREA_H
#define MDI_AREA_H

#include <QMdiArea>


class MdiArea : public QMdiArea
{
public:
    explicit MdiArea(QWidget *parent = nullptr);
};

#endif // MDI_AREA_H
