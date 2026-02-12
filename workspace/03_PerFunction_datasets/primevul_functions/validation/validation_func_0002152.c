QList<QHostAddress> LanLinkProvider::getBroadcastAddresses()
{
    const QStringList customDevices = KdeConnectConfig::instance().customDevices();

    QList<QHostAddress> destinations;
    destinations.reserve(customDevices.length() + 1);


    destinations.append(m_testMode ? QHostAddress::LocalHost : QHostAddress::Broadcast);


    for (auto& customDevice : customDevices) {
        QHostAddress address(customDevice);
        if (address.isNull()) {
            qCWarning(KDECONNECT_CORE) << "Invalid custom device address" << customDevice;
        } else {
            destinations.append(address);
        }
    }

    return destinations;
}
