test_find_suffix()
{
    int at = SuffixArray_find_suffix(sarry, test2, sizeof(test2));
    mu_assert(at != -1, "Failed to find the suffix.");

    at = SuffixArray_find_suffix(sarry, "yo", sizeof("yo"));
    mu_assert(at == -1, "Should fail to find yo.");

    return NULL;
}
