/*
    SPDX-FileCopyrightText: 2022 naracanto https://naracanto.github.io

    SPDX-License-Identifier: GPL-3.0-or-later
*/

#ifndef MDI_DOCUMENT_H
#define MDI_DOCUMENT_H

#include <QWidget>

#include "tabular_document.h"


class MdiDocument : public TabularDocument
{
public:
    explicit MdiDocument(QWidget *parent = nullptr);
};

#endif // MDI_DOCUMENT_H
