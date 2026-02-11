dio_ChkBlock(U2_T Form, U1_T ** Buf, size_t * Size) {
    switch (Form) {
    case FORM_BLOCK1    :
    case FORM_BLOCK2    :
    case FORM_BLOCK4    :
    case FORM_BLOCK     :
    case FORM_DATA1     :
    case FORM_DATA2     :
    case FORM_DATA4     :
    case FORM_DATA8     :
    case FORM_STRING    :
    case FORM_STRP      :
        *Size = dio_gFormDataSize;
        *Buf = (U1_T *)dio_gFormDataAddr;
        break;
    default:
        str_exception(ERR_INV_DWARF, "FORM_BLOCK expected");
    }
}
