vpc_read(BlockDriverState *bs, int64_t sector_num,
                    uint8_t *buf, int nb_sectors)
{
    BDRVVPCState *s = bs->opaque;
    int ret;

    while (nb_sectors > 0) {
	if (!seek_to_sector(bs, sector_num))
	{
	    ret = read(s->fd, buf, 512);
	    if (ret != 512)
		return -1;
	}
	else
            memset(buf, 0, 512);
        nb_sectors--;
        sector_num++;
        buf += 512;
    }
    return 0;
}
