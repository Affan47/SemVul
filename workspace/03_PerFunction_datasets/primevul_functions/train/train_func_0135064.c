_nm_utils_set_testing(NMUtilsTestFlags flags)
{
    g_assert(!NM_FLAGS_ANY(flags, ~NM_UTILS_TEST_ALL));


    flags = (flags & NM_UTILS_TEST_ALL) | (_NM_UTILS_TEST_GENERAL | _NM_UTILS_TEST_INITIALIZED);

    if (!g_atomic_int_compare_and_exchange(&_nm_utils_testing, 0, (int) flags)) {


        g_return_if_reached();
    }
}
