static size_t oncore_payload_cksum_length(unsigned char id1, unsigned char id2)
{
    size_t l;


#define ONCTYPE(id2,id3) ((((unsigned int)id2)<<8)|(id3))


    switch (ONCTYPE(id1,id2)) {
    case ONCTYPE('A','b'): l = 10; break;
    case ONCTYPE('A','w'): l =  8; break;
    case ONCTYPE('A','c'): l = 11; break;
    case ONCTYPE('A','a'): l = 10; break;
    case ONCTYPE('A','d'): l = 11; break;
    case ONCTYPE('A','e'): l = 11; break;
    case ONCTYPE('A','f'): l = 15; break;
    case ONCTYPE('E','a'): l = 76; break;
    case ONCTYPE('A','g'): l =  8; break;
    case ONCTYPE('B','b'): l = 92; break;
    case ONCTYPE('B','j'): l =  8; break;
    case ONCTYPE('A','q'): l =  8; break;
    case ONCTYPE('A','p'): l = 25; break;

    case ONCTYPE('C','h'): l =  9; break;
    case ONCTYPE('C','b'): l = 33; break;
    case ONCTYPE('S','z'): l =  8; break;
    case ONCTYPE('C','j'): l = 294; break;
    case ONCTYPE('F','a'): l =  9; break;
    case ONCTYPE('C','f'): l =  7; break;
    case ONCTYPE('E','q'): l = 96; break;
    case ONCTYPE('A','u'): l = 12; break;
    case ONCTYPE('A','v'): l =  8; break;
    case ONCTYPE('A','N'): l =  8; break;
    case ONCTYPE('A','O'): l =  8; break;
    case ONCTYPE('C','c'): l = 80; break;
    case ONCTYPE('C','k'): l =  7; break;

    case ONCTYPE('B','o'): l =  8; break;
    case ONCTYPE('A','z'): l = 11; break;
    case ONCTYPE('A','y'): l = 11; break;
    case ONCTYPE('A','P'): l =  8; break;
    case ONCTYPE('A','s'): l = 20; break;
    case ONCTYPE('A','t'): l =  8; break;
    case ONCTYPE('E','n'): l = 69; break;
    default:
	return 0;
    }


    return l - 6;
}
