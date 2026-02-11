oneshot_drawcrosshairs( struct mame_bitmap *bitmap, const struct rectangle *cliprect )
{
    int xpos,ypos;

    gun_x_p1 = (readinputport(5) & 0xff) * 320 / 256;
    gun_y_p1 = (readinputport(6) & 0xff) * 240 / 256;


    xpos = gun_x_p1;
    ypos = gun_y_p1;

    gun_x_p1+=gun_x_shift;

    gun_y_p1 -= 0x0a;
    if (gun_y_p1 < 0)
        gun_y_p1=0;


    draw_crosshair( bitmap, xpos, ypos, cliprect );


    gun_x_p2 = (readinputport(7) & 0xff) * 320 / 256;
    gun_y_p2 = (readinputport(8) & 0xff) * 240 / 256;

    xpos = gun_x_p2;
    ypos = gun_y_p2;

    gun_x_p2 += gun_x_shift-0x0a;
    if (gun_x_p2 < 0)
        gun_x_p2=0;


    draw_crosshair( bitmap, xpos, ypos, cliprect );
}
