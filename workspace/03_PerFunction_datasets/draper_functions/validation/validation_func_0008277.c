_dxf_cat_FindCompType( catinfo *cp )
{
    Object o;

    if ( DXGetObjectClass( ( Object ) cp->o ) == CLASS_ARRAY ) {
        o = cp->o;
    }

    else {
        if ( !( o = DXGetComponentValue( ( Field ) cp->o, cp->comp_name ) ) )
            return ERROR;
    }

    cp->comp_array = ( Array ) o;
    cp->comp_data = DXGetArrayData( cp->comp_array );

    if ( !GetObjectSize( o, &cp->num, &cp->obj_size, &cp->comp_type,
                         &cp->comp_rank, cp->comp_shape, &cp->count, &cp->cat_type ) )
        return ERROR;

    cp->intsize = cp->obj_size / sizeof( int );

    cp->remainder = cp->obj_size % sizeof( int );

    switch ( cp->comp_type ) {
    case TYPE_STRING: cp->cmpcat = _dxf_cat_cmp_str; break;
    case TYPE_BYTE: cp->cmpcat = _dxf_cat_cmp_char; break;
    case TYPE_UBYTE: cp->cmpcat = _dxf_cat_cmp_ubyte; break;
    case TYPE_SHORT: cp->cmpcat = _dxf_cat_cmp_short; break;
    case TYPE_USHORT: cp->cmpcat = _dxf_cat_cmp_ushort; break;
    case TYPE_INT: cp->cmpcat = _dxf_cat_cmp_int; break;
    case TYPE_UINT: cp->cmpcat = _dxf_cat_cmp_uint; break;
    case TYPE_FLOAT: cp->cmpcat = _dxf_cat_cmp_float; break;
    case TYPE_DOUBLE: cp->cmpcat = _dxf_cat_cmp_double; break;
    default: cp->cmpcat = _dxf_cat_cmp_any;
    }

    switch ( cp->comp_type ) {
    case TYPE_STRING: cp->hashcmp = _dxf_cat_hashstrcmp; break;
    default: cp->hashcmp = _dxf_cat_hashcmp;
    }

    switch ( cp->comp_type ) {
    case TYPE_STRING: cp->catkey = _dxf_cat_hashstrkey; break;
    default: cp->catkey = _dxf_cat_hashkey;
    }


    return OK;
}
