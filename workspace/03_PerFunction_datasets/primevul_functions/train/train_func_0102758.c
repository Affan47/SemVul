QByteArray Cipher::blowfishCBC(QByteArray cipherText, bool direction)
{
    QCA::Initializer init;
    QByteArray temp = cipherText;
    if (direction)
    {


        while ((temp.length() % 8) != 0) temp.append('\0');

        QCA::InitializationVector iv(8);
        temp.prepend(iv.toByteArray());
    }
    else
    {
        temp = QByteArray::fromBase64(temp);


        while ((temp.length() % 8) != 0) temp.append('\0');
    }

    QCA::Direction dir = (direction) ? QCA::Encode : QCA::Decode;
    QCA::Cipher cipher(m_type, QCA::Cipher::CBC, QCA::Cipher::NoPadding, dir, m_key, QCA::InitializationVector(QByteArray("0")));
    QByteArray temp2 = cipher.update(QCA::MemoryRegion(temp)).toByteArray();
    temp2 += cipher.final().toByteArray();

    if (!cipher.ok())
        return cipherText;

    if (direction)
        temp2 = temp2.toBase64();
    else
        temp2 = temp2.remove(0, 8);

    return temp2;
}
