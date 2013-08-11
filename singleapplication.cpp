/*
 *  QCMA: Cross-platform content manager assistant for the PS Vita
 *
 *  Copyright (C) 2013  Codestation
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "singleapplication.h"

#include <QDebug>
#include <QFile>

const int SingleApplication::timeout = 500;
const QString SingleApplication::SHARED_KEY = "QCMA_KEY";

SingleApplication::SingleApplication(int &argc, char **argv) :
    QApplication(argc, argv)
{
    server = new QLocalServer(this);
    connect(server, SIGNAL(newConnection()), this, SLOT(receiveMessage()));
#ifdef Q_OS_UNIX
    // Make sure that the socket file is deleted
    QFile address(QString("/tmp/" +  SHARED_KEY));

    if(address.exists()) {
        address.remove();
    }

#endif
    server->listen(SHARED_KEY);
}

void SingleApplication::receiveMessage()
{
    QLocalSocket *socket = server->nextPendingConnection();

    if(!socket->waitForReadyRead(timeout)) {
        qDebug() << socket->errorString();
        return;
    }

    QByteArray byteArray = socket->readAll();
    QString message = QString::fromUtf8(byteArray.constData());
    emit messageAvailable(message);
    socket->disconnectFromServer();
}

bool SingleApplication::sendMessage(const QString &message)
{
    QLocalSocket socket;
    socket.connectToServer(SHARED_KEY, QIODevice::WriteOnly);

    if(!socket.waitForConnected(timeout)) {
        return false;
    }

    socket.write(message.toUtf8());

    if(!socket.waitForBytesWritten(timeout)) {
        qDebug() << socket.errorString();
        return false;
    }

    socket.disconnectFromServer();
    return true;
}