encrypt_data(unsigned char* data, int length)
{
    uchar cipher[4096];
    uchar K[128];


    if(data == NULL)                return 1;
    if(length < 1 || length > 2044) return 1;

    if(opt.prga == NULL && opt.crypt != CRYPT_WEP)
    {
        printf("Please specify a WEP key (-w).\n");
        return 1;
    }

    if(opt.prgalen-4 < length && opt.crypt != CRYPT_WEP)
    {
        printf("Please specify a longer PRGA file (-y) with at least %i bytes.\n", (length+4));
        return 1;
    }


    if(opt.crypt == CRYPT_WEP)
    {
        K[0] = rand() & 0xFF;
        K[1] = rand() & 0xFF;
        K[2] = rand() & 0xFF;
        memcpy( K + 3, opt.wepkey, opt.weplen );

        encrypt_wep( data, length, K, opt.weplen+3 );
        memcpy(cipher, data, length);
        memcpy(data+4, cipher, length);
        memcpy(data, K, 3);
        data[3] = 0x00;
    }

    return 0;
}
