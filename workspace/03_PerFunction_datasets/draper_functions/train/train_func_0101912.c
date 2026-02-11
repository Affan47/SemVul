gs_currentcolorscreen(gs_state * pgs, gs_colorscreen_halftone * pht)
{
    int code;

    switch (pgs->halftone->type) {
        case ht_type_colorscreen:
            *pht = pgs->halftone->params.colorscreen;
            return 0;
        default:
            code = gs_currentscreen(pgs, &pht->screens.colored.gray);
            if (code < 0)
                return code;
            pht->screens.colored.red = pht->screens.colored.gray;
            pht->screens.colored.green = pht->screens.colored.gray;
            pht->screens.colored.blue = pht->screens.colored.gray;
            return 0;
    }
}
