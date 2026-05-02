/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
**
** Licensed under the Apache License, Version 2.0 (the "License");
** you may not use this file except in compliance with the License.
** You may obtain a copy of the License at
**
**     http://www.apache.org/licenses/LICENSE-2.0
**
** Unless required by applicable law or agreed to in writing, software
** distributed under the License is distributed on an "AS IS" BASIS,
** WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
** See the License for the specific language governing permissions and
** limitations under the License.
**
****************************************************************************/

#include <QApplication>
#include <QSettings>
#include <QDebug>
#include <QtPlugin>

#ifndef QT_NO_SYSTEMTRAYICON

#include <QMessageBox>
#include "window.h"
#include "lima.h"

#ifndef QT_NO_EMOTICONS
Q_IMPORT_PLUGIN(EmoticonOpenmojiPlugin)
#endif

int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(systray);
#ifndef QT_NO_EMOTICONS
    Q_INIT_RESOURCE(emoticons_openmoji);
#endif

#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
#endif

    QApplication app(argc, argv);

    QSettings settings("lima", "lima-gui");
    QStringList paths = settings.value("paths").value<QStringList>();
    QString program = limactlPath(paths);
    if (program.isEmpty()) {
        QMessageBox::critical(0, QObject::tr("Lima"),
                              QObject::tr("I couldn't find limactl in PATH "
                                          "on this system."));
        return 1;
    }
    if (QSystemTrayIcon::isSystemTrayAvailable()) {
        QApplication::setQuitOnLastWindowClosed(false);
    }

    Window window;
    window.setSettings(&settings);
    window.show();
    return app.exec();
}

#else

#include <QLabel>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QString text("QSystemTrayIcon is not supported on this platform");

    QLabel *label = new QLabel(text);
    label->setWordWrap(true);

    label->show();
    qDebug() << text;

    app.exec();
}

#endif
