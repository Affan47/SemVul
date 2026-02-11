getAlgName(AlgorithmicRange *range, uint32_t code, UCharNameChoice nameChoice,
        char *buffer, uint16_t bufferLength) {
    uint16_t bufferPos=0;


    if(nameChoice==U_UNICODE_10_CHAR_NAME) {

        if(bufferLength>0) {
            *buffer=0;
        }
        return 0;
    }

    switch(range->type) {
    case 0: {

        const char *s=(const char *)(range+1);
        char c;

        uint16_t i, count;


        while((c=*s++)!=0) {
            WRITE_CHAR(buffer, bufferLength, bufferPos, c);
        }


        count=range->variant;


        if(count<bufferLength) {
            buffer[count]=0;
        }

        for(i=count; i>0;) {
            if(--i<bufferLength) {
                c=(char)(code&0xf);
                if(c<10) {
                    c+='0';
                } else {
                    c+='A'-10;
                }
                buffer[i]=c;
            }
            code>>=4;
        }

        bufferPos+=count;
        break;
    }
    case 1: {

        uint16_t indexes[8];
        const uint16_t *factors=(const uint16_t *)(range+1);
        uint16_t count=range->variant;
        const char *s=(const char *)(factors+count);
        char c;


        while((c=*s++)!=0) {
            WRITE_CHAR(buffer, bufferLength, bufferPos, c);
        }

        bufferPos+=writeFactorSuffix(factors, count,
                                     s, code-range->start, indexes, NULL, NULL, buffer, bufferLength);
        break;
    }
    default:


        if(bufferLength>0) {
            *buffer=0;
        }
        break;
    }

    return bufferPos;
}
