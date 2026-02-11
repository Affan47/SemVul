shade_next_flag(shade_coord_stream_t * cs, int BitsPerFlag)
{
    uint flag;
    int code;

    cs->left = 0;
    code = cs->get_value(cs, BitsPerFlag, &flag);
    return (code < 0 ? code : flag);
}
