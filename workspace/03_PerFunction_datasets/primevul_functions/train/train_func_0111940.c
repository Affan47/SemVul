static void vhdx_block_translate(BDRVVHDXState *s, int64_t sector_num,
                                 int nb_sectors, VHDXSectorInfo *sinfo)
{
    uint32_t block_offset;

    sinfo->bat_idx = sector_num >> s->sectors_per_block_bits;


    block_offset = sector_num - (sinfo->bat_idx << s->sectors_per_block_bits);


    sinfo->bat_idx += sinfo->bat_idx >> s->chunk_ratio_bits;


    sinfo->sectors_avail = s->sectors_per_block - block_offset;

    sinfo->bytes_left = sinfo->sectors_avail << s->logical_sector_size_bits;

    if (sinfo->sectors_avail > nb_sectors) {
        sinfo->sectors_avail = nb_sectors;
    }

    sinfo->bytes_avail = sinfo->sectors_avail << s->logical_sector_size_bits;

    sinfo->file_offset = s->bat[sinfo->bat_idx] & VHDX_BAT_FILE_OFF_MASK;

    sinfo->block_offset = block_offset << s->logical_sector_size_bits;


    if (sinfo->file_offset == 0) {
        return;
    }


    sinfo->file_offset += sinfo->block_offset;
}
