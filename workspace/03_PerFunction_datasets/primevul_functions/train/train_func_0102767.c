bool Cipher::encrypt(QByteArray &cipherText)
{
    if (cipherText.left(3) == "+p ")
        cipherText = cipherText.mid(3);
    else
    {
        if (m_cbc)
        {
            QByteArray temp = blowfishCBC(cipherText, true);

            if (temp == cipherText)
            {

                return false;
            }

            cipherText = "+OK *" + temp;
        }
        else
        {
            QByteArray temp = blowfishECB(cipherText, true);

            if (temp == cipherText)
            {

                return false;
            }

            cipherText = "+OK " + temp;
        }
    }
    return true;
}
