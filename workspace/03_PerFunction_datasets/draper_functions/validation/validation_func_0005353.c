UpdateMenu() {
    GxView *V = (GxView *)Active;
    EEventMap *Map = 0;

    if (V)
        Map = V->GetEventMap();

    if (Map != CMap || CMap == 0) {
        const char *NMenu = 0;
        const char *OMenu = 0;


        if (CMap)
            OMenu = CMap->GetMenu(EM_MainMenu);
        if (Map)
            NMenu = Map->GetMenu(EM_MainMenu);
        if (NMenu == 0)
            NMenu = "Main";
        CMap = Map;

        if (OMenu && strcmp(OMenu, NMenu) == 0) {

        } else {
            SetMenu(NMenu);
        }
    }


    GFrame::UpdateMenu();
}
