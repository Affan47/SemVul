ft_stroker_arcto( FT_Stroker  *stroker, s32 side )
{
    Fixed total, rotate;
    Fixed         radius = stroker->radius;
    s32 error  = 0;
    FT_StrokeBorder  border = stroker->borders + side;
    rotate = FT_SIDE_TO_ROTATE( side );
    total = gf_angle_diff( stroker->angle_in, stroker->angle_out);
    if ( total == GF_PI ) total = -rotate * 2;
    error = ft_stroke_border_arcto( border,
                                    &stroker->center,
                                    radius,
                                    stroker->angle_in + rotate,
                                    total );
    border->movable = 0;
    return error;
}
