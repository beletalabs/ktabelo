/*
    SPDX-FileCopyrightText: 2022 naracanto

    SPDX-License-Identifier: GPL-3.0-or-later
*/

#ifndef WINDOW_H
#define WINDOW_H

#include <KXmlGuiWindow>


class Window : public KXmlGuiWindow
{
public:
    explicit Window(QWidget *parent = nullptr);
};

#endif // WINDOW_H
