get_scaled_range(const gs_function_Sd_t *const pfn,
                   const float *lower, const float *upper,
                   int i, float *pw0, float *pw1)
{
    float d0 = pfn->params.Domain[i * 2 + 0], d1 = pfn->params.Domain[i * 2 + 1];
    float v0 = lower[i], v1 = upper[i];
    float e0, e1, w0, w1, w;
    const float small_noise = (float)1e-6;

    if (v0 < d0 || v0 > d1)
        return gs_error_rangecheck;
    if (pfn->params.Encode)
        e0 = pfn->params.Encode[i * 2 + 0], e1 = pfn->params.Encode[i * 2 + 1];
    else
        e0 = 0, e1 = (float)pfn->params.Size[i] - 1;
    w0 = (v0 - d0) * (e1 - e0) / (d1 - d0) + e0;
    if (w0 < 0)
        w0 = 0;
    else if (w0 >= pfn->params.Size[i] - 1)
        w0 = (float)pfn->params.Size[i] - 1;
    w1 = (v1 - d0) * (e1 - e0) / (d1 - d0) + e0;
    if (w1 < 0)
        w1 = 0;
    else if (w1 >= pfn->params.Size[i] - 1)
        w1 = (float)pfn->params.Size[i] - 1;
    if (w0 > w1) {
        w = w0; w0 = w1; w1 = w;
    }
    if (floor(w0 + 1) - w0 < small_noise * any_abs(e1 - e0))
        w0 = (floor(w0) + 1);
    if (w1 - floor(w1) < small_noise * any_abs(e1 - e0))
        w1 = floor(w1);
    if (w0 > w1)
        w0 = w1;
    *pw0 = w0;
    *pw1 = w1;
    return 0;
}
