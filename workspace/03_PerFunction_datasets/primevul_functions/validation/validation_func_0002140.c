void LanLinkProvider::addLink(const QString& deviceId, QSslSocket* socket, NetworkPacket* receivedPacket, LanDeviceLink::ConnectionStarted connectionOrigin)
{

    disconnect(socket, &QAbstractSocket::disconnected, socket, &QObject::deleteLater);

    LanDeviceLink* deviceLink;

    QMap< QString, LanDeviceLink* >::iterator linkIterator = m_links.find(deviceId);
    if (linkIterator != m_links.end()) {

        deviceLink = linkIterator.value();
        deviceLink->reset(socket, connectionOrigin);
    } else {
        deviceLink = new LanDeviceLink(deviceId, this, socket, connectionOrigin);

        disconnect(socket, &QAbstractSocket::disconnected, socket, &QObject::deleteLater);
        bool isDeviceTrusted = KdeConnectConfig::instance().trustedDevices().contains(deviceId);
        if (!isDeviceTrusted && m_links.size() > MAX_UNPAIRED_CONNECTIONS) {
            qCWarning(KDECONNECT_CORE) << "Too many unpaired devices to remember them all. Ignoring " << deviceId;
            socket->disconnectFromHost();
            socket->deleteLater();
            return;
        }
        connect(deviceLink, &QObject::destroyed, this, &LanLinkProvider::deviceLinkDestroyed);
        m_links[deviceId] = deviceLink;
        if (m_pairingHandlers.contains(deviceId)) {


            Q_ASSERT(m_pairingHandlers.contains(deviceId));
            m_pairingHandlers[deviceId]->setDeviceLink(deviceLink);
        }
    }
    Q_EMIT onConnectionReceived(*receivedPacket, deviceLink);
}
