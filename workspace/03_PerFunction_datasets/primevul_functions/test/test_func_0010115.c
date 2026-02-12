tmx_m_zone(union DateData *x)
{
    VALUE zone = m_zone(x);

    return RSTRING_PTR(zone);
}
