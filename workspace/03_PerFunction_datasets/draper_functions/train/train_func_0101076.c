spif_str_casecmp_with_ptr(spif_str_t self, spif_charptr_t other)
{
    int c;

    SPIF_OBJ_COMP_CHECK_NULL(self, other);
    c = strcasecmp(SPIF_CHARPTR_C(SPIF_STR_STR(self)), SPIF_CHARPTR_C(other));
    return SPIF_CMP_FROM_INT(c);
}
