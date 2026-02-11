snefru512_setup(void)
{
    int             index;
    int             rotation;
    int             i;
    static int      havesetuphash;

    if (havesetuphash)
        return;
    for (index = 0; index < SBOXCOUNT; index++)
        for (rotation = 0; rotation < 4; rotation++)
            for (i = 0; i < 256; i++)
                snefru512_rotated[rotation][index][i] =
                    (
                        (
                            (uint32)snefru512_sboxes[index][i]
                        >>
                            (rotation * 8)
                        )
                    |
                        (
                            (uint32)snefru512_sboxes[index][i]
                        <<
                            (32 - rotation * 8)
                        )
                    );
    havesetuphash = 1;
}
