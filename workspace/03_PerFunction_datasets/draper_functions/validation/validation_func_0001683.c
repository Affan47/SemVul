acorn128_enc_onebyte(unsigned char *state, unsigned char plaintextbyte,
       unsigned char *ciphertextbyte, unsigned char *ksbyte, unsigned char cabyte, unsigned char cbbyte)
{
    unsigned char i;
    unsigned char plaintextbit,ciphertextbit,kstem,ca,cb;

    *ciphertextbyte = 0;
    kstem = 0;
    *ksbyte = 0;
    for (i = 0; i < 8; i++)
    {
        ca = (cabyte >> i) & 1;
        cb = (cbbyte >> i) & 1;
        plaintextbit = (plaintextbyte >> i) & 1;
        Encrypt_StateUpdate128(state, plaintextbit, &ciphertextbit, &kstem, ca, cb);
        *ciphertextbyte |= (ciphertextbit << i);
        *ksbyte |= (kstem << i);
    }
}
