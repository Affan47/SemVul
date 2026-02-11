string_attr_init (Dwarf_P_Debug dbg,
    Dwarf_Signed section_index,
    unsigned count)
{
    Dwarf_P_Per_Sect_String_Attrs sect_sa = &dbg->de_sect_string_attr[section_index];

    sect_sa->sect_sa_n_alloc = count;
    sect_sa->sect_sa_list = NULL;
    if (count > 0) {
        sect_sa->sect_sa_section_number = section_index;
        sect_sa->sect_sa_list = _dwarf_p_get_alloc(dbg,
            sizeof(struct Dwarf_P_String_Attr_s) * sect_sa->sect_sa_n_alloc);
        if (sect_sa->sect_sa_list == NULL) {
            sect_sa->sect_sa_n_alloc = 0;
            return -1;
        }
    }
    return 0;
}
