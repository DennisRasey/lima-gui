/****************************************************************************
**
** Copyright (C) 2021 Anders F Björklund
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

#ifndef WINDOW_H
#define WINDOW_H

#include <QSystemTrayIcon>

#ifndef QT_NO_SYSTEMTRAYICON

#include <QDialog>
#include <QProcess>

QT_BEGIN_NAMESPACE
class QAction;
class QCheckBox;
class QComboBox;
class QDialog;
class QFile;
class QGroupBox;
class QIcon;
class QLineEdit;
class QTableView;
class QMainWindow;
class QMenu;
class QPushButton;
class QTemporaryDir;
class QTextEdit;
class QSettings;
QT_END_NAMESPACE

#include "instance.h"
#include "templates.h"

//! [0]
class Window : public QDialog
{
    Q_OBJECT

public:
    Window();

    void setVisible(bool visible) override;
    void setSettings(QSettings *settings);

protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    void setIcon(int index);
    void iconActivated(QSystemTrayIcon::ActivationReason reason);
    void updateButtons();
    void inspectInstance();
    void aboutProgram();
    void startedCommand();
    void finishedCommand(int code, QProcess::ExitStatus status);

private:
    QString getVersion();
    InstanceList getInstances();
    InstanceHash getInstanceHash();
    void createInstanceGroupBox();
    void createActions();
    void createTrayIcon();

    QString selectedInstance();
    void setSelectedInstance(QString instance);
    void updateInstances();
    void updateQuiet(int state);
    void shellConsole();
    void displayWindow();
    bool getProcessOutput(QStringList arguments, QString &text);
    void yamlEditor(QString instanceName, QString setString, QString yamlFile, bool create,
                    bool edit, bool embed, bool start);
    void createEditor();
    void createEditorSet(QString set);
    QWidget *newTemplateButton(QString name);
    void updateEmbed();
    void quickCreate();
    void urlCreate();
    void advancedCreate();
    QString quickSetString();
    void setChanged(const QString &);
    void quickInstance();
    void sendCommand(QString cmd);
    void sendCommand(QStringList cmds);
    QString outputCommand(QStringList cmds);
    QString shellCommand(QString instanceName, QStringList cmds);
    void helpDocs();
    void findYAML();
    void loadYAML();
    void readYAML(QString fileName);
    void saveYAML();
    void writeYAML(QString fileName);
    QFile *tempYAML(QString name);
    void embedYAML(QString name);
    QFile *validateYAML(QString name);
    void createInstance();
    void createInstanceURL();
    void updateInstance();
    void startInstance();
    void stopInstance();
    void viewInstance();
    void editInstance();
    void messageInstance();
    bool askConfirm(QString instance);
    void removeInstance();

    QComboBox *iconComboBox;

    QMainWindow *editWindow;
    QDialog *quickDialog;
    QCheckBox *quickPreview;
    QCheckBox *quickEmbed;
    QCheckBox *quickStart;
    QTemporaryDir *editDir;
    QFile *editFile;
    QLineEdit *createName;
    QLineEdit *createSet;
    QPushButton *createHelp;
    QLineEdit *createFind;
    QCheckBox *createEmbed;
    QCheckBox *createStart;
    QTextEdit *createYAML;
    QLineEdit *createURL;

    QGroupBox *instanceGroupBox;
    InstanceModel *instanceModel;
    QTableView *instanceListView;
    QCheckBox *instanceListQuiet;
    QPushButton *createButton;
    QPushButton *quickButton;
    QPushButton *aboutButton;
    QPushButton *refreshButton;
    QPushButton *shellButton;
    QPushButton *displayButton;
    QPushButton *startButton;
    QPushButton *stopButton;
    QPushButton *inspectButton;
    QPushButton *removeButton;

    QAction *minimizeAction;
    QAction *maximizeAction;
    QAction *restoreAction;
    QAction *aboutAction;
    QAction *aboutQtAction;
    QAction *quitAction;

    QProcess *process;
    QSystemTrayIcon *trayIcon;
    QMenu *trayIconMenu;
    QIcon *trayIconIcon;

    QSettings *settings;
};
//! [0]

#endif // QT_NO_SYSTEMTRAYICON

#endif
