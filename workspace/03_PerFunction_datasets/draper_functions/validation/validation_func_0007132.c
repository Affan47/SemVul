com_constructor(mca_btl_openib_com_frag_t *frag)
{
    mca_btl_openib_frag_t *base_frag = to_base_frag(frag);
    mca_btl_openib_reg_t* reg =
        (mca_btl_openib_reg_t*)base_frag->base.super.registration;

    frag->registration = reg;

    if(reg) {
        frag->sg_entry.lkey = reg->mr->lkey;
        base_frag->segment.key = reg->mr->lkey;
    }
    frag->n_wqes_inflight = 0;
}
