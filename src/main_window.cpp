/*
    SPDX-FileCopyrightText: 2022 naracanto

    SPDX-License-Identifier: GPL-3.0-or-later
*/

#include "main_window.h"

#include <QApplication>

#include <KActionCollection>
#include <KStandardAction>


MainWindow::MainWindow(QWidget *parent)
    : KXmlGuiWindow(parent)
{
    setupActions();
}


void MainWindow::setupActions()
{
    KStandardAction::quit(qApp, &QCoreApplication::quit, actionCollection());

    setupGUI(Default, QLatin1String("tabelo_ui.rc"));
}
