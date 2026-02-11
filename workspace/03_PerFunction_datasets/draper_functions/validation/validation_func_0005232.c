hdrl_mask_to_bpm(const cpl_mask * mask, uint64_t flag)
{
    cpl_ensure(mask, CPL_ERROR_NULL_INPUT, NULL);

    cpl_ensure(flag <= CX_MAXUINT, CPL_ERROR_UNSUPPORTED_MODE, NULL);
    unsigned int iflag = (unsigned int)flag;
    const size_t nx = cpl_mask_get_size_x(mask);
    const size_t ny = cpl_mask_get_size_y(mask);
    cpl_image * bpm = cpl_image_new(nx, ny, CPL_TYPE_INT);
    const cpl_binary * dmsk = cpl_mask_get_data_const(mask);
    unsigned int * data = (unsigned int *)cpl_image_get_data_int(bpm);

    for (size_t i = 0; i < ny * nx; i++) {
        data[i] = dmsk[i] ? iflag : 0;
    }

    return bpm;
}
