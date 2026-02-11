dwarf_compress_integer_block(
    Dwarf_P_Debug    dbg,
    Dwarf_Bool       unit_is_signed,
    Dwarf_Small      unit_length_in_bits,
    void*            input_block,
    Dwarf_Unsigned   input_length_in_units,
    Dwarf_Unsigned*  output_length_in_bytes_ptr,
    Dwarf_Error*     error
)
{
    Dwarf_Unsigned output_length_in_bytes = 0;
    char * output_block = 0;
    char encode_buffer[ENCODE_SPACE_NEEDED];
    int i = 0;
    char * ptr = 0;
    int remain = 0;
    int result = 0;

    if (dbg == NULL) {
        _dwarf_p_error(NULL, error, DW_DLE_DBG_NULL);
        return((void *)DW_DLV_BADADDR);
    }

    if (unit_is_signed == false ||
        unit_length_in_bits != 32 ||
        input_block == NULL ||
        input_length_in_units == 0 ||
        output_length_in_bytes_ptr == NULL) {

        _dwarf_p_error(NULL, error, DW_DLE_BADBITC);
        return ((void *) DW_DLV_BADADDR);
    }


    output_length_in_bytes = 0;
    for (i=0; i<input_length_in_units; i++) {
        int unit_encoded_size;
        Dwarf_sfixed unit;

        unit = ((Dwarf_sfixed*)input_block)[i];

        result = _dwarf_pro_encode_signed_leb128_nm(unit, &unit_encoded_size,
            encode_buffer,sizeof(encode_buffer));
        if (result !=  DW_DLV_OK) {
            _dwarf_p_error(dbg, error, DW_DLE_ALLOC_FAIL);
            return((Dwarf_P_Attribute)DW_DLV_BADADDR);
        }
        output_length_in_bytes += unit_encoded_size;
    }


    output_block = (void *)
        _dwarf_p_get_alloc(dbg, output_length_in_bytes);
    if (output_block == NULL) {
        _dwarf_p_error(dbg, error, DW_DLE_ALLOC_FAIL);
        return((void*)DW_DLV_BADADDR);
    }


    ptr = output_block;
    remain = output_length_in_bytes;
    for (i=0; i<input_length_in_units; i++) {
        int unit_encoded_size;
        Dwarf_sfixed unit;

        unit = ((Dwarf_sfixed*)input_block)[i];

        result = _dwarf_pro_encode_signed_leb128_nm(unit, &unit_encoded_size,
            ptr, remain);
        if (result !=  DW_DLV_OK) {
            _dwarf_p_error(dbg, error, DW_DLE_ALLOC_FAIL);
            return((Dwarf_P_Attribute)DW_DLV_BADADDR);
        }
        remain -= unit_encoded_size;
        ptr += unit_encoded_size;
    }

    if (remain != 0) {
        _dwarf_p_dealloc(dbg, (unsigned char *)output_block);
        _dwarf_p_error(dbg, error, DW_DLE_ALLOC_FAIL);
        return((Dwarf_P_Attribute)DW_DLV_BADADDR);
    }

    *output_length_in_bytes_ptr = output_length_in_bytes;
    return (void*) output_block;

}
