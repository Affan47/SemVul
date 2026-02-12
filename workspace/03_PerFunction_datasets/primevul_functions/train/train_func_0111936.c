static int vhdx_write_header(BlockDriverState *bs_file, VHDXHeader *hdr,
                             uint64_t offset, bool read)
{
    uint8_t *buffer = NULL;
    int ret;
    VHDXHeader header_le;

    assert(bs_file != NULL);
    assert(hdr != NULL);


    buffer = qemu_blockalign(bs_file, VHDX_HEADER_SIZE);
    if (read) {

        ret = bdrv_pread(bs_file, offset, buffer, VHDX_HEADER_SIZE);
        if (ret < 0) {
            goto exit;
        }
    } else {
        memset(buffer, 0, VHDX_HEADER_SIZE);
    }


    memcpy(buffer, hdr, sizeof(VHDXHeader));
    hdr->checksum = vhdx_update_checksum(buffer, VHDX_HEADER_SIZE,
                                         offsetof(VHDXHeader, checksum));
    vhdx_header_le_export(hdr, &header_le);
    ret = bdrv_pwrite_sync(bs_file, offset, &header_le, sizeof(VHDXHeader));

exit:
    qemu_vfree(buffer);
    return ret;
}
