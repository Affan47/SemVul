operator<<(unsigned char ch)
{
    if( (ch > 96) && (ch < 123))
    {

        ch -= 97;
    }
    else if( (ch > 64) && (ch < 91))
    {

        ch -= 65;
    }
    else if( (ch >47) && (ch < 58))
    {

        ch -= 22;
    }
    else
    {

        switch( ch ) {
            case 33: ch = 36; break;
            case 34: ch = 37; break;
            case 38: ch = 38; break;
            case 39: ch = 39; break;
            case 40: ch = 40; break;
            case 41: ch = 41; break;
            case 43: ch = 42; break;
            case 44: ch = 43; break;
            case 45: ch = 44; break;
            case 46: ch = 45; break;
            case 47: ch = 46; break;
            case 58: ch = 47; break;
            case 59: ch = 48; break;
            case 61: ch = 49; break;
            case 63: ch = 50; break;
            case 64: ch = 51; break;
            case 95: ch = 52; break;
            default: ch = 255; break;
        }
    }

    if(ch != 255)
        *this<<morse_symbol(map[ch]);

    return *this;
}
