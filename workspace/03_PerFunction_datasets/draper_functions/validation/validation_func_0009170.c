ReadSintB()
{

    int val = ReadUintB();
    bool bit;


    if (val != 0)
    {
        bit = ReadBitB();
        if (bit )
            val = -val;
    }
    return val;
}
