resize_callb(AW_window *aw,AW_CL cd1,AW_CL cd2)
{
    AWUSE(aw);AWUSE(cd1);AWUSE(cd2);
    if(PH_display::ph_display)
    {
        PH_display::ph_display->resized();
        PH_display::ph_display->display();
    }
}
