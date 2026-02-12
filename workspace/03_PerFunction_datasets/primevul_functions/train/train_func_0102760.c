bool Cipher::setKey(QByteArray key)
{
    if (key.isEmpty()) {
        m_key.clear();
        return false;
    }

    if (key.mid(0, 4).toLower() == "ecb:")
    {
        m_cbc = false;
        m_key = key.mid(4);
    }

    else if (key.mid(0, 4).toLower() == "cbc:")
    {
        m_cbc = true;
        m_key = key.mid(4);
    }
    else
    {


        m_cbc = false;
        m_key = key;
    }
    return true;
}
