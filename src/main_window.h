/*
    SPDX-FileCopyrightText: 2022 naracanto https://naracanto.github.io

    SPDX-License-Identifier: GPL-3.0-or-later
*/

#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <KXmlGuiWindow>

class KRecentFilesAction;

class MdiArea;
class MdiDocument;


class MainWindow : public KXmlGuiWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    bool openDocumentFromUrl(const QUrl &url);

private:
    void setupActions();

    bool loadDocument(const QUrl &url);
    MdiDocument *createDocument();

private Q_SLOTS:
    void newDocument();
    void openDocument();
    void saveDocument();
    void saveDocumentAs();

private:
    MdiArea *m_documentsArea;

    KRecentFilesAction *m_actionRecentDocuments;
};

#endif // MAIN_WINDOW_H
