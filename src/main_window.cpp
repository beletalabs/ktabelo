/*
    SPDX-FileCopyrightText: 2022 naracanto https://naracanto.github.io

    SPDX-License-Identifier: GPL-3.0-or-later
*/

#include "main_window.h"

#include <QApplication>
#include <QDebug>
#include <QFileDialog>
#include <QMenuBar>
#include <QMdiSubWindow>

#include <KActionCollection>
#include <KLocalizedString>
#include <KMessageBox>
#include <KStandardAction>
#include <KToggleAction>
#include <KToggleFullScreenAction>

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
    KStandardAction::open(this, &MainWindow::openDocuments, actionCollection());

    m_actionRecentDocuments = KStandardAction::openRecent(this, &MainWindow::openDocument, actionCollection());

    KStandardAction::save(this, &MainWindow::saveDocument, actionCollection());
    KStandardAction::saveAs(this, &MainWindow::saveDocumentAs, actionCollection());
    KStandardAction::close(m_documentsArea, &MdiArea::closeActiveSubWindow, actionCollection());

    auto *actionCloseOther = new QAction(i18n("Close Other"), this);
    actionCloseOther->setToolTip(i18n("Close other open documents"));
    actionCollection()->addAction(QStringLiteral("file_close_other"), actionCloseOther);
    connect(actionCloseOther, &QAction::triggered, this, &MainWindow::closeOtherDocuments);

    auto *actionCloseAll = new QAction(i18n("Close All"), this);
    actionCloseAll->setToolTip(i18n("Close all open documents"));
    actionCollection()->addAction(QStringLiteral("file_close_all"), actionCloseAll);
    connect(actionCloseAll, &QAction::triggered, this, &MainWindow::closeAllDocuments);

    KStandardAction::quit(qApp, &QCoreApplication::quit, actionCollection());


    //
    // View

    auto *actionViewFullScreen = KStandardAction::fullScreen(this, &MainWindow::viewFullScreen, this, actionCollection());
    actionCollection()->setDefaultShortcut(actionViewFullScreen, Qt::Key_F11);


    //
    // Settings

    auto *actionShowMenubar = KStandardAction::showMenubar(menuBar(), &QMenuBar::setVisible, actionCollection());


    // Standard window options
    setupGUI(Default, QLatin1String("tabelo_ui.rc"));

    // Initialization
    actionShowMenubar->setChecked(!menuBar()->isHidden());
}


MdiDocument *MainWindow::createDocument()
{
    MdiDocument *document = new MdiDocument;
    m_documentsArea->addSubWindow(document);
    m_documentsArea->updateSubWindowTitle(document);
    connect(document, &MdiDocument::urlChanged, m_documentsArea, [=](){ m_documentsArea->updateSubWindowTitle(document); });

    return document;
}


void MainWindow::newDocument()
{
    qDebug() << "Create new document";

    auto *document = createDocument();
    document->show();
}


void MainWindow::openDocuments()
{
    for (const QUrl &url : QFileDialog::getOpenFileUrls(this, i18n("Open Document")))
        openDocument(url);
}


bool MainWindow::openDocument(const QUrl &url)
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


void MainWindow::saveDocument()
{

}


void MainWindow::saveDocumentAs()
{

}


void MainWindow::closeOtherDocuments()
{
    if (m_documentsArea->subWindowList().size() > 1
        && KMessageBox::warningContinueCancel(this,
                                              i18n("This will close all open documents beside the current one. Are you sure you want to continue?"),
                                              i18n("Close all documents beside current one"),
                                              KStandardGuiItem::cont(),
                                              KStandardGuiItem::cancel(),
                                              QStringLiteral("closeOther"))
            != KMessageBox::Cancel) {

        m_documentsArea->closeOtherSubWindows();
    }
}


void MainWindow::closeAllDocuments()
{
    if (!m_documentsArea->subWindowList().empty()
        && KMessageBox::warningContinueCancel(this,
                                              i18n("This will close all open documents. Are you sure you want to continue?"),
                                              i18n("Close all documents"),
                                              KStandardGuiItem::cont(),
                                              KStandardGuiItem::cancel(),
                                              QStringLiteral("closeAll"))
            != KMessageBox::Cancel) {

        m_documentsArea->closeAllSubWindows();
    }
}


void MainWindow::viewFullScreen(bool fullScreen)
{
    KToggleFullScreenAction::setFullScreen(this, fullScreen);
}
