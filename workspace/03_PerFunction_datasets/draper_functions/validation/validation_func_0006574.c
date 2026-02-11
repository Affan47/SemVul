_dwarf_cleanup_llbuf(Dwarf_Debug dbg, Dwarf_Locdesc ** llbuf, int count)
{
    int i;
    for (i = 0; i < count; ++i) {
        dwarf_dealloc(dbg, llbuf[i]->ld_s, DW_DLA_LOC_BLOCK);
        dwarf_dealloc(dbg, llbuf[i], DW_DLA_LOCDESC);
    }
    dwarf_dealloc(dbg, llbuf, DW_DLA_LIST);
}
