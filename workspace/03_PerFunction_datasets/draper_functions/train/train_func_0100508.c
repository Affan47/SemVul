fli_draw_text_inside( int          align,
                      FL_Coord     x,
                      FL_Coord     y,
                      FL_Coord     w,
                      FL_Coord     h,
                      const char * istr,
                      int          style,
                      int          size,
                      FL_COLOR     c,
                      FL_COLOR     bc,
                      int          bk )
{
    int special = 0;
    int xoff,
        yoff;
    char *str;
    int sw = w,
        sh = h,
        sx = x,
        sy = y;

    if ( ! istr || ! *istr )
        return;

    str = fl_strdup( istr );

    if ( str[ 0 ] == '@' && str[ 1 ] != '@' )
    {
        if ( w < 5 && h < 5 )
        {
            sw = sh = 6 + 1.1 * size;
            sx -= sw / 2;
            sy -= sh / 2;
        }

        if ( fl_draw_symbol( str, sx, sy, sw, sh, c ) )
        {
            fl_free( str );
            return;
        }
        else
            str[ 0 ] = ' ';
    }

    if ( str[ 0 ] == '@' )
        str++;

    xoff = 5;
    yoff = 4;

    x += xoff;
    w -= 2 * xoff;
    y += yoff;
    h -= 2 * yoff;

    if ( special_style( style ) )
    {
        special = ( style / FL_SHADOW_STYLE ) * FL_SHADOW_STYLE;
        style %= FL_SHADOW_STYLE;
    }


    if ( special == FL_SHADOW_STYLE )
        D( x + 2, y + 2, FL_BOTTOM_BCOL );
    else if ( special == FL_ENGRAVED_STYLE )
    {
        D( x - 1, y,     FL_RIGHT_BCOL );
        D( x,     y - 1, FL_RIGHT_BCOL );
        D( x - 1, y - 1, FL_RIGHT_BCOL );
        D( x + 1, y,     FL_TOP_BCOL );
        D( x,     y + 1, FL_TOP_BCOL );
        D( x + 1, y + 1, FL_TOP_BCOL );
    }
    else if ( special == FL_EMBOSSED_STYLE )
    {
        D( x - 1, y,     FL_TOP_BCOL );
        D( x,     y - 1, FL_TOP_BCOL );
        D( x - 1, y - 1, FL_TOP_BCOL );
        D( x + 1, y,     FL_RIGHT_BCOL );
        D( x,     y + 1, FL_RIGHT_BCOL );
        D( x + 1, y + 1, FL_RIGHT_BCOL );
    }

    fli_draw_text_cursor( align, x, y, w, h, str, style, size,
                          c, bc, 0, special ? 0 : bk, -1 );

    fl_free( str );
}
