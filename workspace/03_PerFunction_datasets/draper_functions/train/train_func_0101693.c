kdtree_fits_write_chunk(kdtree_fits_t* io, fitsbin_chunk_t* chunk) {
    fitsbin_t* fb = kdtree_fits_get_fitsbin(io);
    if (fitsbin_write_chunk(fb, chunk)) {
        ERROR("Failed to write kdtree extra chunk");
        return -1;
    }
    return 0;
}
