/*
    SPDX-FileCopyrightText: 2022 naracanto

    SPDX-License-Identifier: GPL-3.0-or-later
*/

#ifndef WINDOW_H
#define WINDOW_H

#include <KXmlGuiWindow>


class MainWindow : public KXmlGuiWindow
{
public:
    explicit MainWindow(QWidget *parent = nullptr);

private:
    void setupActions();
};

#endif // WINDOW_H
