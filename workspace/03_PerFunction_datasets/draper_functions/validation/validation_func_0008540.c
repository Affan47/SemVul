dwarf_get_fde_range(Dwarf_Fde fde,
    Dwarf_Addr * low_pc,
    Dwarf_Unsigned * func_length,
    Dwarf_Ptr * fde_bytes,
    Dwarf_Unsigned * fde_byte_length,
    Dwarf_Off * cie_offset,
    Dwarf_Signed * cie_index,
    Dwarf_Off * fde_offset, Dwarf_Error * error)
{
    Dwarf_Debug dbg;

    if (fde == NULL) {
        _dwarf_error(NULL, error, DW_DLE_FDE_NULL);
        return (DW_DLV_ERROR);
    }

    dbg = fde->fd_dbg;
    if (dbg == NULL) {
        _dwarf_error(NULL, error, DW_DLE_FDE_DBG_NULL);
        return (DW_DLV_ERROR);
    }


    if (low_pc != NULL)
        *low_pc = fde->fd_initial_location;
    if (func_length != NULL)
        *func_length = fde->fd_address_range;
    if (fde_bytes != NULL)
        *fde_bytes = fde->fd_fde_start;
    if (fde_byte_length != NULL)
        *fde_byte_length = fde->fd_length;
    if (cie_offset != NULL)
        *cie_offset = fde->fd_cie_offset;
    if (cie_index != NULL)
        *cie_index = fde->fd_cie_index;
    if (fde_offset != NULL)
        *fde_offset = fde->fd_fde_start - fde->fd_section_ptr;

    return DW_DLV_OK;
}
