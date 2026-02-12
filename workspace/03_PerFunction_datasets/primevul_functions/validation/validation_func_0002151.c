void LanLinkProvider::tcpSocketConnected()
{
    QSslSocket* socket = qobject_cast<QSslSocket*>(sender());

    if (!socket) return;

#if QT_VERSION < QT_VERSION_CHECK(5,15,0)
    disconnect(socket, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error), this, &LanLinkProvider::connectError);
#else
    disconnect(socket, &QAbstractSocket::errorOccurred, this, &LanLinkProvider::connectError);
#endif

    configureSocket(socket);


    connect(socket, &QAbstractSocket::disconnected, socket, &QObject::deleteLater);

    NetworkPacket* receivedPacket = m_receivedIdentityPackets[socket].np;
    const QString& deviceId = receivedPacket->get<QString>(QStringLiteral("deviceId"));


    NetworkPacket np2(QLatin1String(""));
    NetworkPacket::createIdentityPacket(&np2);
    socket->write(np2.serialize());
    bool success = socket->waitForBytesWritten();

    if (success) {

        qCDebug(KDECONNECT_CORE) << "TCP connection done (i'm the existing device)";


        if (receivedPacket->get<int>(QStringLiteral("protocolVersion")) >= MIN_VERSION_WITH_SSL_SUPPORT) {

            bool isDeviceTrusted = KdeConnectConfig::instance().trustedDevices().contains(deviceId);
            configureSslSocket(socket, deviceId, isDeviceTrusted);

            qCDebug(KDECONNECT_CORE) << "Starting server ssl (I'm the client TCP socket)";

            connect(socket, &QSslSocket::encrypted, this, &LanLinkProvider::encrypted);

            connect(socket, QOverload<const QList<QSslError> &>::of(&QSslSocket::sslErrors), this, &LanLinkProvider::sslErrors);

            socket->startServerEncryption();

            return;
        } else {
            qWarning() << receivedPacket->get<QString>(QStringLiteral("deviceName")) << "uses an old protocol version, this won't work";

        }

    } else {


        qCDebug(KDECONNECT_CORE) << "Fallback (2), try reverse connection (send udp packet)";
        m_udpSocket.writeDatagram(np2.serialize(), m_receivedIdentityPackets[socket].sender, m_udpBroadcastPort);
    }

    delete m_receivedIdentityPackets.take(socket).np;

}
