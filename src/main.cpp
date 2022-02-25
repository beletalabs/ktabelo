/*
    SPDX-FileCopyrightText: 2022 naracanto

    SPDX-License-Identifier: GPL-3.0-or-later
*/

#include <QApplication>
#include <QCommandLineParser>

#include <KAboutData>
#include <KLocalizedString>

#include "window.h"


int main (int argc, char *argv[])
{
    QApplication app(argc, argv);

    KLocalizedString::setApplicationDomain("tabelo");


    //
    // Infomation about this application

    KAboutData aboutData(
        QStringLiteral("tabelo"),
        i18n("Tabelo"),
        QStringLiteral("0.1.0"),
        i18n("A table editor based on Qt/KF for C++"),
        KAboutLicense::GPL_V3,
        i18n("(c) 2022 The Tabelo authors"),
        i18n("An open source table editor written in C++ using the Qt and KDE frameworks"),
        QStringLiteral("https://github.com/tabeloapp/tabelo")
    );
    aboutData.setOrganizationDomain(QByteArray("github.com/tabeloapp"));

    aboutData.addAuthor(i18n("naracanto"), i18n("Creator"), QString(), QStringLiteral("https://naracanto.com"));

    KAboutData::setApplicationData(aboutData);


    // Command line
    QCommandLineParser parser;
    aboutData.setupCommandLine(&parser);
    parser.process(app);
    aboutData.processCommandLine(&parser);

    Window *window = new Window();
    window->show();

    return app.exec();
}
