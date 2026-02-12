QByteArray Cipher::decrypt(QByteArray cipherText)
{
    QByteArray pfx = "";
    bool error = false;


    if (cipherText.mid(0, 5) == "+OK *")
    {

        if (m_cbc)
            cipherText = cipherText.mid(5);

        else
        {
            cipherText = cipherText.mid(5);
            pfx = "ERROR_NONECB: ";
            error = true;
        }
    }

    else if (cipherText.mid(0, 4) == "+OK " || cipherText.mid(0, 5) == "mcps ")
    {

        if (m_cbc)
        {
            cipherText = (cipherText.mid(0, 4) == "+OK ") ? cipherText.mid(4) : cipherText.mid(5);
            pfx = "ERROR_NONCBC: ";
            error = true;
        }

        else
        {
            if (cipherText.mid(0, 4) == "+OK ")
                cipherText = cipherText.mid(4);
            else
                cipherText = cipherText.mid(5);
        }
    }

    else
        return cipherText;

    QByteArray temp;

    if ((m_cbc && !error) || (!m_cbc && error))
    {
        cipherText = cipherText;
        temp = blowfishCBC(cipherText, false);

        if (temp == cipherText)
        {

            return cipherText+' '+'\n';
        }
        else
            cipherText = temp;
    }
    else
    {
        temp = blowfishECB(cipherText, false);

        if (temp == cipherText)
        {

            return cipherText+' '+'\n';
        }
        else
            cipherText = temp;
    }


    if (cipherText.at(0) == 1)
        pfx = "\x0";
    cipherText = pfx+cipherText+' '+'\n';
    return cipherText;
}
