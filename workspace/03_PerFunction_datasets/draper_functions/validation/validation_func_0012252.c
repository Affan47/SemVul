ustr_u32cat(struct UString *dst, UChar32 c, UErrorCode *status){
    if(c > 0x10FFFF){
        *status = U_ILLEGAL_CHAR_FOUND;
        return;
    }
    if(c >0xFFFF){
        ustr_ucat(dst, U16_LEAD(c), status);
        ustr_ucat(dst, U16_TRAIL(c), status);
    }else{
        ustr_ucat(dst, (UChar) c, status);
    }
}
