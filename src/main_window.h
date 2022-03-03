/*
    SPDX-FileCopyrightText: 2022 naracanto https://naracanto.github.io

    SPDX-License-Identifier: GPL-3.0-or-later
*/

#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <KXmlGuiWindow>

class KRecentFilesAction;

class MainWindowArea;


class MainWindow : public KXmlGuiWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    void openDocumentFromFile(const QUrl &fileName);

private:
    void setupActions();

    KRecentFilesAction *m_actionRecentDocuments {nullptr};

private Q_SLOTS:
    void newDocument();
    void openDocument();
    void saveDocument();
    void saveDocumentAs();

private:
    MainWindowArea *m_windowArea;
};

#endif // MAIN_WINDOW_H
