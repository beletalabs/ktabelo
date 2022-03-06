/*
    SPDX-FileCopyrightText: 2022 naracanto https://naracanto.github.io

    SPDX-License-Identifier: GPL-3.0-or-later
*/

#include "main_window.h"

#include <QApplication>
#include <QDebug>
#include <QFileDialog>
#include <QMenuBar>

#include <KActionCollection>
#include <KLocalizedString>
#include <KStandardAction>
#include <KToggleAction>

#include "mdi_area.h"
#include "mdi_document.h"


MainWindow::MainWindow(QWidget *parent)
    : KXmlGuiWindow(parent)
    , m_documentsArea{new MdiArea}
    , m_actionRecentDocuments{nullptr}
{
    m_documentsArea->setViewMode(QMdiArea::TabbedView);
    m_documentsArea->setDocumentMode(true);
    m_documentsArea->setTabsClosable(true);
    m_documentsArea->setTabsMovable(true);
    setCentralWidget(m_documentsArea);

    setupActions();
}


void MainWindow::setupActions()
{
    //
    // File

    KStandardAction::openNew(this, &MainWindow::newDocument, actionCollection());
    KStandardAction::open(this, &MainWindow::openDocument, actionCollection());

    m_actionRecentDocuments = KStandardAction::openRecent(this, &MainWindow::openDocumentFromUrl, actionCollection());

    KStandardAction::save(this, &MainWindow::saveDocument, actionCollection());
    KStandardAction::saveAs(this, &MainWindow::saveDocumentAs, actionCollection());
    KStandardAction::quit(qApp, &QCoreApplication::quit, actionCollection());


    //
    // Settings

    auto *actionShowMenubar = KStandardAction::showMenubar(menuBar(), &QMenuBar::setVisible, actionCollection());


    // Standard window options
    setupGUI(Default, QLatin1String("tabelo_ui.rc"));

    // Initialization
    actionShowMenubar->setChecked(!menuBar()->isHidden());
}


void MainWindow::newDocument()
{
    qDebug() << "Create new document";

    auto *document = createDocument();
    document->show();
}


void MainWindow::openDocument()
{
    for (const QUrl &url : QFileDialog::getOpenFileUrls(this, i18n("Open Document")))
        openDocumentFromUrl(url);
}


bool MainWindow::openDocumentFromUrl(const QUrl &url)
{
    qDebug() << "Open document:" << url.toString();

    if (auto *subWindow = m_documentsArea->findSubWindow(url)) {
        // Given document is already loaded; activate the subwindow
        m_documentsArea->setActiveSubWindow(subWindow);

        m_actionRecentDocuments->addUrl(url);

        return true;
    }

    return loadDocument(url);
}


bool MainWindow::loadDocument(const QUrl &url)
{
    auto *document = createDocument();

    if (!document->load(url)) {
        // Given document could not be loaded
        document->close();
        return false;
    }

    document->show();

    m_actionRecentDocuments->addUrl(url);

    return true;
}


MdiDocument *MainWindow::createDocument()
{
    MdiDocument *document = new MdiDocument;
    m_documentsArea->addSubWindow(document);
    m_documentsArea->updateSubWindowTitle(document);
    connect(document, &MdiDocument::urlChanged, m_documentsArea, [=](){ m_documentsArea->updateSubWindowTitle(document); });

    return document;
}


void MainWindow::saveDocument()
{

}


void MainWindow::saveDocumentAs()
{

}
