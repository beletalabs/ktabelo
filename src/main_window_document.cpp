/*
    SPDX-FileCopyrightText: 2022 naracanto https://naracanto.github.io

    SPDX-License-Identifier: GPL-3.0-or-later
*/

#include "main_window_document.h"

#include <KLocalizedString>


MainWindowDocument::MainWindowDocument(QWidget *parent)
    : QWidget(parent)
{
    static int sequenceNumber = 1;

    setWindowTitle(i18n("Untitled (%1)", sequenceNumber++));
}
