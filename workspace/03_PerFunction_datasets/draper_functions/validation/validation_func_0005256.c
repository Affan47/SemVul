gs_cie_defx_scale(float *values, const gs_range *range, int dim)
{
    double scale = (dim - 1.0) / (range->rmax - range->rmin);
    int i;

    for (i = 0; i < gx_cie_cache_size; ++i) {
        float value = values[i];

        values[i] =
            (value <= range->rmin ? 0 :
             value >= range->rmax ? dim - 1 :
             (value - range->rmin) * scale);
    }
}
