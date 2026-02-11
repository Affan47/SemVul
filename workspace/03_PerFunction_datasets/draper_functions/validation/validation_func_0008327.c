main (void)
{
    int		nerrors=0;
    hid_t	fapl;

    h5_reset();
    fapl = h5_fileaccess();

    nerrors += test_1(fapl);
    nerrors += test_2(fapl);
    nerrors += test_3(fapl);
    nerrors += test_4(fapl);
    nerrors += test_ooo_indices(fapl);


    nerrors += (h5_verify_cached_stabs(FILENAME, fapl) < 0 ? 1 : 0);

    if (nerrors) goto error;

    puts("All global heap tests passed.");
    h5_cleanup(FILENAME, fapl);
    return 0;

 error:
    puts("*** TESTS FAILED ***");
    return 1;
}
