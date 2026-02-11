ubifs_pack_lsave(struct ubifs_info *c, void *buf, int *lsave)
{
	uint8_t *addr = buf + UBIFS_LPT_CRC_BYTES;
	int i, pos = 0;
	uint16_t crc;

	pack_bits(&addr, &pos, UBIFS_LPT_LSAVE, UBIFS_LPT_TYPE_BITS);
	for (i = 0; i < c->lsave_cnt; i++)
		pack_bits(&addr, &pos, lsave[i], c->lnum_bits);
	crc = crc16(-1, buf + UBIFS_LPT_CRC_BYTES,
		    c->lsave_sz - UBIFS_LPT_CRC_BYTES);
	addr = buf;
	pos = 0;
	pack_bits(&addr, &pos, crc, UBIFS_LPT_CRC_BITS);
}
