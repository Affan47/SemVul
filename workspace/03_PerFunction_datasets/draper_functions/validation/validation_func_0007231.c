init(AD_MAIN * gb_ptr)

{
    if (ad_main != 0)       {
        return new AD_ERR("AD_SAI: no reinit\n");
    }
    if (gb_ptr->gbd) {
        ad_main = gb_ptr;
        gb_main = gb_ptr->gbd;
        last = count = 0;
        AD_READWRITE::gbdataptr = 0;
        return 0;
    }
    else    {
        return new AD_ERR("SAI init (NULL)\n");
    }
}
