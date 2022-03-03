/*
    SPDX-FileCopyrightText: 2022 naracanto https://naracanto.github.io

    SPDX-License-Identifier: GPL-3.0-or-later
*/

#include "mdi_document.h"

#include <KLocalizedString>


MdiDocument::MdiDocument(QWidget *parent)
    : TabularDocument(parent)
{
    static int sequenceNumber = 1;

    setWindowTitle(i18n("Untitled (%1)", sequenceNumber++));
}
