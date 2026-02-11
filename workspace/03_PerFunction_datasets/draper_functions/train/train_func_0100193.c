SIO_SizeOfSector(UBYTE unit, int sector, int *sz, ULONG *ofs)
{
	int size;
	ULONG offset;
	int header_size = (image_type[unit] == IMAGE_TYPE_ATR ? 16 : 0);

	if (BINLOAD_start_binloading) {
		if (sz)
			*sz = 128;
		if (ofs)
			*ofs = 0;
		return;
	}

	if (image_type[unit] == IMAGE_TYPE_PRO) {
		size = 128;
		offset = 16 + (128+12)*(sector -1);
	}
	else if (image_type[unit] == IMAGE_TYPE_VAPI) {
		vapi_additional_info_t *info;
		vapi_sec_info_t *secinfo;

		size = 128;
		info = additional_info[unit];
		if (info == NULL)
			offset = 0;
		else if (sector > sectorcount[unit])
			offset = 0;
		else {
			secinfo = &info->sectors[sector-1];
			if (secinfo->sec_count == 0  )
				offset = 0;
			else
				offset = secinfo->sec_offset[0];
		}
	}
	else if (sector < 4) {

		size = 128;
		offset = header_size + (sector - 1) * (boot_sectors_type[unit] == BOOT_SECTORS_PHYSICAL ? 256 : 128);
	}
	else {
		size = sectorsize[unit];
		offset = header_size + (boot_sectors_type[unit] == BOOT_SECTORS_LOGICAL ? 0x180 : 0x300) + (sector - 4) * size;
	}

	if (sz)
		*sz = size;

	if (ofs)
		*ofs = offset;
}
