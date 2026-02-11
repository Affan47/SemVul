makeDoGKernel(l_int32    halfheight,
              l_int32    halfwidth,
              l_float32  stdev,
              l_float32  ratio)
{
l_int32    sx, sy, i, j;
l_float32  pi, squaredist, highnorm, lownorm, val;
L_KERNEL  *kel;

    PROCNAME("makeDoGKernel");

    sx = 2 * halfwidth + 1;
    sy = 2 * halfheight + 1;
    if ((kel = kernelCreate(sy, sx)) == NULL)
        return (L_KERNEL *)ERROR_PTR("kel not made", procName, NULL);
    kernelSetOrigin(kel, halfheight, halfwidth);

    pi = 3.1415926535;
    for (i = 0; i < sy; i++) {
        for (j = 0; j < sx; j++) {
            squaredist = (l_float32)((i - halfheight) * (i - halfheight) +
                                     (j - halfwidth) * (j - halfwidth));
            highnorm = 1. / (2 * stdev * stdev);
            lownorm = highnorm / (ratio * ratio);
            val = (highnorm / pi) * expf(-(highnorm * squaredist)) -
                  (lownorm / pi) * expf(-(lownorm * squaredist));
            kernelSetElement(kel, i, j, val);
        }
    }

    return kel;
}
