dwarf_create_cie_from_start(Dwarf_Debug dbg,
    Dwarf_Small * cie_ptr_val,
    Dwarf_Small * section_ptr,
    Dwarf_Unsigned section_index,
    Dwarf_Unsigned section_length,
    Dwarf_Small * frame_ptr_end,
    Dwarf_Unsigned cie_id_value,
    Dwarf_Unsigned cie_count,
    int use_gnu_cie_calc,
    Dwarf_Cie * cie_ptr_to_use_out,
    Dwarf_Error * error)
{
    struct cie_fde_prefix_s prefix;
    int res = DW_DLV_ERROR;
    Dwarf_Small *frame_ptr = cie_ptr_val;

    if (frame_ptr < section_ptr || frame_ptr > frame_ptr_end) {
        _dwarf_error(dbg, error, DW_DLE_DEBUG_FRAME_LENGTH_BAD);
        return DW_DLV_ERROR;
    }


    memset(&prefix, 0, sizeof(prefix));
    res = dwarf_read_cie_fde_prefix(dbg, frame_ptr, section_ptr,
        section_index, section_length,
        &prefix, error);
    if (res == DW_DLV_ERROR) {
        return res;
    }
    if (res == DW_DLV_NO_ENTRY) {

        _dwarf_error(dbg, error, DW_DLE_FRAME_CIE_DECODE_ERROR);
        return DW_DLV_ERROR;

    }

    if (prefix.cf_cie_id != cie_id_value) {
        _dwarf_error(dbg, error, DW_DLE_FRAME_CIE_DECODE_ERROR);
        return DW_DLV_ERROR;
    }
    frame_ptr = prefix.cf_addr_after_prefix;
    res = dwarf_create_cie_from_after_start(dbg,
        &prefix,
        section_ptr,
        frame_ptr,
        cie_count,
        use_gnu_cie_calc,
        cie_ptr_to_use_out, error);
    return res;

}
