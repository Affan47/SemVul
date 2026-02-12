void LanLinkProvider::configureSslSocket(QSslSocket* socket, const QString& deviceId, bool isDeviceTrusted)
{

    QList<QSslCipher> socketCiphers;
    socketCiphers.append(QSslCipher(QStringLiteral("ECDHE-ECDSA-AES256-GCM-SHA384")));
    socketCiphers.append(QSslCipher(QStringLiteral("ECDHE-ECDSA-AES128-GCM-SHA256")));
    socketCiphers.append(QSslCipher(QStringLiteral("ECDHE-RSA-AES128-SHA")));


    QSslConfiguration sslConfig;
    sslConfig.setCiphers(socketCiphers);
    sslConfig.setLocalCertificate(KdeConnectConfig::instance().certificate());

    QFile privateKeyFile(KdeConnectConfig::instance().privateKeyPath());
    QSslKey privateKey;
    if (privateKeyFile.open(QIODevice::ReadOnly)) {
        privateKey = QSslKey(privateKeyFile.readAll(), QSsl::Rsa);
    }
    privateKeyFile.close();
    sslConfig.setPrivateKey(privateKey);

    if (isDeviceTrusted) {
        QString certString = KdeConnectConfig::instance().getDeviceProperty(deviceId, QStringLiteral("certificate"), QString());
        sslConfig.setCaCertificates({QSslCertificate(certString.toLatin1())});
        sslConfig.setPeerVerifyMode(QSslSocket::VerifyPeer);
    } else {
        sslConfig.setPeerVerifyMode(QSslSocket::QueryPeer);
    }
    socket->setSslConfiguration(sslConfig);
    socket->setPeerVerifyName(deviceId);


}
