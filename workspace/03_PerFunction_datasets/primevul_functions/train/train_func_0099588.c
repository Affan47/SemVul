bool set_preferred_target_page_bits(int bits)
{


#ifdef TARGET_PAGE_BITS_VARY
    assert(bits >= TARGET_PAGE_BITS_MIN);
    if (target_page_bits == 0 || target_page_bits > bits) {
        if (target_page_bits_decided) {
            return false;
        }
        target_page_bits = bits;
    }
#endif
    return true;
}
