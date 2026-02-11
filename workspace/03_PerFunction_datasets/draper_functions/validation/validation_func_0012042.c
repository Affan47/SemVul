dfb_gfxcard_get_capabilities( CardCapabilities *ret_caps )
{
     D_ASSERT( card != NULL );

     D_ASSERT( ret_caps != NULL );

     *ret_caps = card->caps;
}
