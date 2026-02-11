MakeDummyRfmBlock(void)
{
    RfmBlock new;

    if (RFM_ModuleCurrent->dummy_block) {
        return(RFM_ModuleCurrent->dummy_block);
    }
    new = GET_RFM_BLOCK_TABLE();
    new->block_kind = RFM_BLOCK_DUMMY;
    new->module = RFM_ModuleCurrent;
    RFM_ModuleCurrent->dummy_block = new;
    return(new);
}
