static int stsdin(int size)
{

    u32in();

    if (u32in() != 1)
        return ERR_FAIL;

    return size;
};
