fix_lim_of_iv_and_heap_module(Module_table *mpt)
{
    Iv_table *ipt;
    Heap_table *hpt;

    for (ipt = mpt->invisible_head; ipt != NULL; ipt = ipt->next) {
        fix_lim_of_iv(ipt, mpt);
    }
    for (hpt = mpt->heap_head; hpt != NULL; hpt = hpt->next) {
        fix_lim_of_heap(hpt, mpt);
    }
}
