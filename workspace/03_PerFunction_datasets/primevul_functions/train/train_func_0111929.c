static void vhdx_update_bat_table_entry(BlockDriverState *bs, BDRVVHDXState *s,
                                       VHDXSectorInfo *sinfo,
                                       uint64_t *bat_entry_le,
                                       uint64_t *bat_offset, int state)
{


    s->bat[sinfo->bat_idx]  = sinfo->file_offset;

    s->bat[sinfo->bat_idx] |= state & VHDX_BAT_STATE_BIT_MASK;

    *bat_entry_le = cpu_to_le64(s->bat[sinfo->bat_idx]);
    *bat_offset = s->bat_offset + sinfo->bat_idx * sizeof(VHDXBatEntry);

}
