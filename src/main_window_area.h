/*
    SPDX-FileCopyrightText: 2022 naracanto https://naracanto.github.io

    SPDX-License-Identifier: GPL-3.0-or-later
*/

#ifndef MAIN_WINDOW_AREA_H
#define MAIN_WINDOW_AREA_H

#include <QMdiArea>


class MainWindowArea : public QMdiArea
{
public:
    explicit MainWindowArea(QWidget *parent = nullptr);
};

#endif // MAIN_WINDOW_AREA_H
