fn_scale_functions(gs_function_t ***ppsfns, const gs_function_t *const *pfns,
                   int count, const gs_range_t *pranges, bool step_ranges,
                   gs_memory_t *mem)
{
    gs_function_t **psfns;
    int code = alloc_function_array(count, &psfns, mem);
    const gs_range_t *ranges = pranges;
    int i;

    if (code < 0)
        return code;
    for (i = 0; i < count; ++i) {
        int code = gs_function_make_scaled(pfns[i], &psfns[i], ranges, mem);

        if (code < 0) {
            fn_free_functions((const gs_function_t *const *)psfns, count, mem);
            return code;
        }
        if (step_ranges)
            ++ranges;
    }
    *ppsfns = psfns;
    return 0;
}
