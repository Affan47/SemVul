gx_psconcretize_CIEDEFG(const gs_client_color * pc, const gs_color_space * pcs,
                      frac * pconc, const gs_imager_state * pis)
{
    const gs_cie_defg *pcie = pcs->params.defg;
    int i;
    fixed hijk[4];
    frac abc[3];
    cie_cached_vector3 vec3;
    int code;

    if_debug4m('c', pis->memory, "[c]concretize DEFG [%g %g %g %g]\n",
               pc->paint.values[0], pc->paint.values[1],
               pc->paint.values[2], pc->paint.values[3]);
    code = gx_cie_check_rendering_inline(pcs, pconc, pis);
    if (code < 0)
        return code;
    if (code == 1)
        return 0;


    for (i = 0; i < 4; ++i) {
        int tdim = pcie->Table.dims[i] - 1;
        double factor = pcie->caches_defg.DecodeDEFG[i].floats.params.factor;
        double v0 = pc->paint.values[i];
        const gs_range *const rangeDEFG = &pcie->RangeDEFG.ranges[i];
        double value =
            (v0 < rangeDEFG->rmin ? 0.0 : factor *
            (v0 > rangeDEFG->rmax ? rangeDEFG->rmax - rangeDEFG->rmin :
             v0 - rangeDEFG->rmin ));
        int vi = (int)value;
        double vf = value - vi;
        double v = pcie->caches_defg.DecodeDEFG[i].floats.values[vi];

        if (vf != 0 && vi < factor)
            v += vf *
                (pcie->caches_defg.DecodeDEFG[i].floats.values[vi + 1] - v);
        v = (v < 0 ? 0 : v > tdim ? tdim : v);
        hijk[i] = float2fixed(v);
    }

    gx_color_interpolate_linear(hijk, &pcie->Table, abc);

#define SCALE_TO_RANGE(range, frac) ( \
       float2cie_cached(((range).rmax - (range).rmin) * frac2float(frac) + \
            (range).rmin) \
    )

    vec3.u = SCALE_TO_RANGE(pcie->RangeABC.ranges[0], abc[0]);
    vec3.v = SCALE_TO_RANGE(pcie->RangeABC.ranges[1], abc[1]);
    vec3.w = SCALE_TO_RANGE(pcie->RangeABC.ranges[2], abc[2]);

    if (!pis->cie_joint_caches->skipDecodeABC)
        cie_lookup_map3(&vec3 , &pcie->caches.DecodeABC,
                        "Decode/MatrixABC");
    GX_CIE_REMAP_FINISH(vec3, pconc, pis, pcs);
    return 0;
}
