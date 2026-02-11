quant_param_array(gs_param_float_array * pfa, int count, const UINT16 * pvals,
                  floatp QFactor, gs_memory_t * mem)
{
    float *data;
    int i;

    data = (float *)gs_alloc_byte_array(mem, count, sizeof(float),
                                        "quant_param_array");

    if (data == 0)
        return_error(gs_error_VMerror);
    for (i = 0; i < count; ++i)
        data[i] = pvals[jpeg_inverse_order(i)] / QFactor;
    pfa->data = data;
    pfa->size = count;
    pfa->persistent = true;
    return 0;
}
