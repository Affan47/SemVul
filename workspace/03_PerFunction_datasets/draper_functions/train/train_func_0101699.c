save_preview (string path)
{
    drawing_area da (0, 0, screen::length () >> 1, screen::height () >> 1);
    image temp (da.length (), da.height());
    image preview (72, 54);

    mapview *view = data::engine->get_mapview ();
    mapsquare_area *area = data::engine->get_landmap ()->get_submap
        (data::the_player->submap ());

    u_int16 offx = 0;
    u_int16 offy = 0;


    if (area->area_length () * MAPSQUARE_SIZE < view->length ())
        offx = (view->length () - area->area_length () * MAPSQUARE_SIZE) >> 1;
    if (area->area_height () * MAPSQUARE_SIZE < view->height ())
        offy = (view->height () - area->area_height () * MAPSQUARE_SIZE) >> 1;


    s_int16 x = (data::the_player->posx () - view->posx ()) * MAPSQUARE_SIZE + offx;
    s_int16 y = (data::the_player->posy () - view->posy ()) * MAPSQUARE_SIZE + offy;


    u_int16 length = da.length() >> 1;
    u_int16 height = da.height() >> 1;


    if (x + length > screen::length ()) x = -da.length ();
    else if (x - length < 0) x = 0;
    else x = length - x;

    if (y + height > screen::height ()) y = -da.height ();
    else if (y - height < 0) y = 0;
    else y = height - y;

    data::engine->draw (x, y, &da, &temp);
    preview.zoom (temp);
    preview.save_pnm (path);
}
