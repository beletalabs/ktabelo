/*
    SPDX-FileCopyrightText: 2022 naracanto https://naracanto.github.io

    SPDX-License-Identifier: GPL-3.0-or-later
*/

#include <QApplication>
#include <QCommandLineParser>
#include <QDir>
#include <QUrl>

#include <KAboutData>
#include <KLocalizedString>

#include "main_window.h"


int main (int argc, char *argv[])
{
    QApplication app(argc, argv);

    KLocalizedString::setApplicationDomain("ktabelo");


    //
    // About

    KAboutData aboutData(
        QStringLiteral("ktabelo"),
        i18n("KTabelo"),
        QStringLiteral("0.1.0"),
        i18n("A table editor based on Qt/KF for C++"),
        KAboutLicense::GPL_V3,
        i18n("(c) 2022 The KTabelo authors"),
        i18n("An open source table editor written in C++ using the Qt and KDE frameworks"),
        QStringLiteral("https://github.com/beletalabs/ktabelo")
    );
    aboutData.setOrganizationDomain(QByteArray("beletalabs.github.io"));

    aboutData.addAuthor(i18n("naracanto"), i18n("Creator"), QString(), QStringLiteral("https://naracanto.github.io"));

    KAboutData::setApplicationData(aboutData);


    //
    // Command line

    QCommandLineParser parser;
    aboutData.setupCommandLine(&parser);

    parser.addPositionalArgument(QStringLiteral("urls"), i18n("Documents to open."), QStringLiteral("[urls...]"));
    parser.process(app);

    aboutData.processCommandLine(&parser);


    auto *window = new MainWindow();
    for(const QString &url : parser.positionalArguments()) {
        window->openDocument(QUrl::fromUserInput(url, QDir::currentPath()));
    }
    window->show();

    return app.exec();
}
