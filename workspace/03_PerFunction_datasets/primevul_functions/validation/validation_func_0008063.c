getRGBFromOctcube(l_int32   cubeindex,
                  l_int32   level,
                  l_int32  *prval,
                  l_int32  *pgval,
                  l_int32  *pbval)
{
l_int32  rgbindex;


    rgbindex = cubeindex << (3 * (7 - level));
    rgbindex |= (0x7 << (3 * (6 - level)));


    *prval = ((rgbindex >> 13) & 0x80) |
             ((rgbindex >> 11) & 0x40) |
             ((rgbindex >> 9) & 0x20) |
             ((rgbindex >> 7) & 0x10) |
             ((rgbindex >> 5) & 0x08) |
             ((rgbindex >> 3) & 0x04) |
             ((rgbindex >> 1) & 0x02);
    *pgval = ((rgbindex >> 12) & 0x80) |
             ((rgbindex >> 10) & 0x40) |
             ((rgbindex >> 8) & 0x20) |
             ((rgbindex >> 6) & 0x10) |
             ((rgbindex >> 4) & 0x08) |
             ((rgbindex >> 2) & 0x04) |
             (rgbindex & 0x02);
    *pbval = ((rgbindex >> 11) & 0x80) |
             ((rgbindex >> 9) & 0x40) |
             ((rgbindex >> 7) & 0x20) |
             ((rgbindex >> 5) & 0x10) |
             ((rgbindex >> 3) & 0x08) |
             ((rgbindex >> 1) & 0x04) |
             ((rgbindex << 1) & 0x02);

    return;
}
