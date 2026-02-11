test_select_hyper_contig_dr(hid_t dset_type, hid_t xfer_plist)
{
    int test_num = 0;
    unsigned chunk_edge_size;
    unsigned edge_size = 6;
    unsigned small_rank;
    unsigned large_rank;
    uint16_t *cube_buf;
    uint16_t *zero_buf;
    uint16_t *cube_ptr;
    unsigned max_rank = 5;
    size_t max_cube_size;
    size_t s;
    unsigned u;


    MESSAGE(5, ("Testing Contiguous Hyperslabs With Different Rank I/O Functionality\n"));


    max_cube_size = (size_t)1;
    for(u = 0; u < max_rank; u++)
        max_cube_size *= (size_t)edge_size;


    cube_buf = (uint16_t *)HDmalloc(sizeof(uint16_t) * max_cube_size);
    CHECK(cube_buf, NULL, "HDmalloc");


    cube_ptr = cube_buf;
    for(s = 0; s < max_cube_size; s++)
        *cube_ptr++ = (uint16_t)s;


    zero_buf = (uint16_t *)HDcalloc(sizeof(uint16_t), max_cube_size);
    CHECK(zero_buf, NULL, "HDcalloc");

    for(large_rank = 1; large_rank <= max_rank; large_rank++) {
        for(small_rank = 1; small_rank < large_rank; small_rank++) {
            chunk_edge_size = 0;
            test_select_hyper_contig_dr__run_test(test_num, cube_buf, zero_buf,
                    edge_size, chunk_edge_size, small_rank, large_rank,
                    dset_type, xfer_plist);
            test_num++;

            chunk_edge_size = 3;
            test_select_hyper_contig_dr__run_test(test_num, cube_buf, zero_buf,
                    edge_size, chunk_edge_size, small_rank, large_rank,
                    dset_type, xfer_plist);
            test_num++;
        }
    }

    HDfree(cube_buf);
    HDfree(zero_buf);

}
