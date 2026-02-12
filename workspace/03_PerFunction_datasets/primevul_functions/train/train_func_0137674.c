dwarf_convert_to_global_offset(Dwarf_Attribute attr,
    Dwarf_Off offset,
    Dwarf_Off * ret_offset,
    Dwarf_Error * error)
{
    Dwarf_Debug dbg = 0;
    Dwarf_CU_Context cu_context = 0;
    int res = 0;

    res  = get_attr_dbg(&dbg,&cu_context,attr,error);
    if (res != DW_DLV_OK) {
        return res;
    }
    switch (attr->ar_attribute_form) {
    case DW_FORM_ref1:
    case DW_FORM_ref2:
    case DW_FORM_ref4:
    case DW_FORM_ref8:
    case DW_FORM_ref_udata:


        offset += cu_context->cc_debug_offset;

        break;

    case DW_FORM_ref_addr:


        break;
    default: {
        dwarfstring m;

        dwarfstring_constructor(&m);
        dwarfstring_append_printf_u(&m,
            "DW_DLE_BAD_REF_FORM. The form "
            "code is 0x%x which cannot be converted to a global "
            " offset by "
            "dwarf_convert_to_global_offset()",
            attr->ar_attribute_form);
        _dwarf_error_string(dbg, error, DW_DLE_BAD_REF_FORM,
            dwarfstring_string(&m));
        dwarfstring_destructor(&m);
        return DW_DLV_ERROR;
        }
    }

    *ret_offset = (offset);
    return DW_DLV_OK;
}
