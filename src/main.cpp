/*
    SPDX-FileCopyrightText: 2022 naracanto

    SPDX-License-Identifier: GPL-3.0-or-later
*/

#include <QApplication>

#include "window.h"


int main (int argc, char *argv[])
{
    QApplication app(argc, argv);

    Window *window = new Window();
    window->show();

    return app.exec();
}
