static int vhdx_open_region_tables(BlockDriverState *bs, BDRVVHDXState *s)
{
    int ret = 0;
    uint8_t *buffer;
    int offset = 0;
    VHDXRegionTableEntry rt_entry;
    uint32_t i;
    bool bat_rt_found = false;
    bool metadata_rt_found = false;


    buffer = qemu_blockalign(bs, VHDX_HEADER_BLOCK_SIZE);

    ret = bdrv_pread(bs->file, VHDX_REGION_TABLE_OFFSET, buffer,
                     VHDX_HEADER_BLOCK_SIZE);
    if (ret < 0) {
        goto fail;
    }
    memcpy(&s->rt, buffer, sizeof(s->rt));
    vhdx_region_header_le_import(&s->rt);
    offset += sizeof(s->rt);

    if (!vhdx_checksum_is_valid(buffer, VHDX_HEADER_BLOCK_SIZE, 4) ||
        memcmp(&s->rt.signature, "regi", 4)) {
        ret = -EINVAL;
        goto fail;
    }


    if (s->rt.entry_count > 2047) {
        ret = -EINVAL;
        goto fail;
    }

    for (i = 0; i < s->rt.entry_count; i++) {
        memcpy(&rt_entry, buffer + offset, sizeof(rt_entry));
        offset += sizeof(rt_entry);

        vhdx_region_entry_le_import(&rt_entry);


        ret = vhdx_region_check(s, rt_entry.file_offset, rt_entry.length);
        if (ret < 0) {
            goto fail;
        }

        vhdx_region_register(s, rt_entry.file_offset, rt_entry.length);


        if (guid_eq(rt_entry.guid, bat_guid)) {

            if (bat_rt_found) {
                ret = -EINVAL;
                goto fail;
            }
            bat_rt_found = true;
            s->bat_rt = rt_entry;
            continue;
        }

        if (guid_eq(rt_entry.guid, metadata_guid)) {

            if (metadata_rt_found) {
                ret = -EINVAL;
                goto fail;
            }
            metadata_rt_found = true;
            s->metadata_rt = rt_entry;
            continue;
        }

        if (rt_entry.data_bits & VHDX_REGION_ENTRY_REQUIRED) {


            ret = -ENOTSUP;
            goto fail;
        }
    }

    if (!bat_rt_found || !metadata_rt_found) {
        ret = -EINVAL;
        goto fail;
    }

    ret = 0;

fail:
    qemu_vfree(buffer);
    return ret;
}
