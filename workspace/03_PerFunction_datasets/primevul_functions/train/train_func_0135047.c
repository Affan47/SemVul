nm_utils_get_testing()
{
    NMUtilsTestFlags flags;

again:
    flags = (NMUtilsTestFlags) _nm_utils_testing;
    if (flags != NM_UTILS_TEST_NONE) {

        return flags & NM_UTILS_TEST_ALL;
    }


    flags = _NM_UTILS_TEST_INITIALIZED;
    if (g_test_initialized())
        flags |= _NM_UTILS_TEST_GENERAL;

    g_atomic_int_compare_and_exchange(&_nm_utils_testing, 0, (int) flags);


    goto again;
}
