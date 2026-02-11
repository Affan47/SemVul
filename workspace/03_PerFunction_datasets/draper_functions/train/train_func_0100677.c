isBinaryData( const QString &fileName )
{
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly))
        return false;
    const QByteArray data = file.read(32);
    return isBufferBinaryData(data);
}
