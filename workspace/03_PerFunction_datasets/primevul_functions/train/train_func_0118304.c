void *WavFileBase::getConvBuffer(int sizeBytes)
{
    if (convBuffSize < sizeBytes)
    {
        delete[] convBuff;

        convBuffSize = (sizeBytes + 15) & -8;
        convBuff = new char[convBuffSize];
    }
    return convBuff;
}
