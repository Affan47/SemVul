set_route(const PolyLine& route)
{
    if (&_display_route == &route)
    {
        db_printf("Error:\tTrying to update libavoid route with itself.\n");
        return;
    }
    _display_route.ps = route.ps;


}
