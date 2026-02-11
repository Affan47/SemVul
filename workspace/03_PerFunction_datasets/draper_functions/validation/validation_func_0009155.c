us_mtc_set_total_frames( us_mtc_t *self, int32_t total_frames )
{
    uint8_t max_frame = us_mtc_max_frame[self->m_fmt];
    if ( us_mtc_is_drop[self->m_fmt] )
    {
        int32_t etf = total_frames - ( 2 + ( ( total_frames / 17980 ) * 2 ) );
        total_frames += ( 2 * ( etf / 1798 ) ) - ( 2 * ( etf / 17980 ) );
    }
    self->m_frame = total_frames % max_frame;
    self->m_second = ( total_frames / max_frame ) % 60;
    self->m_minute = ( total_frames / ( max_frame * 60 ) ) % 60;
    self->m_hour = ( total_frames / ( max_frame * 3600 ) ) % 24;
}
