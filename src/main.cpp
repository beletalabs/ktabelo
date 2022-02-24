/*
    SPDX-FileCopyrightText: 2022 naracanto

    SPDX-License-Identifier: GPL-3.0-or-later
*/

#include <QApplication>

#include <KLocalizedString>

#include "window.h"


int main (int argc, char *argv[])
{
    QApplication app(argc, argv);

    KLocalizedString::setApplicationDomain("tabelo");

    Window *window = new Window();
    window->show();

    return app.exec();
}
