static void FillISO885915( XML_Encoding *info )
{


    for( int i = 0x00; i < 0xA4; ++i)
        info->map[i] = i;
    info->map[0xA4] = 0x20AC;
    info->map[0xA5] = 0xA5;
    info->map[0xA6] = 0x0160;
    info->map[0xA7] = 0xA7;
    info->map[0xA8] = 0x0161;
    for( int i = 0xA9; i < 0xB4; ++i )
        info->map[i] = i;
    info->map[0xB4] = 0x017D;
    for( int i = 0xB5; i < 0xB8; ++i )
        info->map[i] = i;
    info->map[0xB8] = 0x017E;
    for( int i = 0xB9; i < 0xBC; ++i )
        info->map[i] = i;
    info->map[0xBC] = 0x0152;
    info->map[0xBD] = 0x0153;
    info->map[0xBE] = 0x0178;
    for( int i = 0xBF; i < 0x100; ++i )
        info->map[i] = i;
}
