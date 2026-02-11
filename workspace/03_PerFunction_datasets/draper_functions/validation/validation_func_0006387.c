wpa_client(struct ST_info *st_cur,uchar* tag, int length)
{
    if(tag == NULL)
        return 1;

    if(st_cur == NULL)
        return 1;

    if(tag[0] != 0xDD && tag[0] != 0x30)
        return 1;

    if(tag[0] == 0xDD)
    {
        if(length < 24)
            return 1;

        switch(tag[17]) {
            case 0x02:
                st_cur->wpahash = 1;
                break;
            case 0x04:
                st_cur->wpahash = 2;
                break;
            default:
                return 1;
        }

        st_cur->wpatype = 1;
    }

    if(tag[0] == 0x30 && st_cur->wpatype == 0)
    {
        if(length < 22)
            return 1;

        switch(tag[13]) {
            case 0x02:
                st_cur->wpahash = 1;
                break;
            case 0x04:
                st_cur->wpahash = 2;
                break;
            default:
                return 1;
        }

        st_cur->wpatype = 2;
    }

    return 0;
}
