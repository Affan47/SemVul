p_fetch_videoframe_via_cache(GapPlayerMainGlobalParams *gpp
                   , char *gva_videofile
                   , gint32 framenumber
                   , gint32 rangesize
                   , gint32 seltrack
                   , gdouble delace
                   , const char *preferred_decoder
                   , gint32 *th_bpp_ptr
                   , gint32 *th_width_ptr
                   , gint32 *th_height_ptr
                   , gint32 *flip_status_ptr
                   , const gchar *ckey
                   )
{
  guchar *th_data;

  th_data = p_fetch_frame_via_cache(gpp
              , ckey
              , th_bpp_ptr
              , th_width_ptr
              , th_height_ptr
              , flip_status_ptr
              );
  if(th_data == NULL)
  {
    th_data = p_fetch_videoframe(gpp
                , gva_videofile
                , framenumber
                , rangesize
                , seltrack
                , delace
                , preferred_decoder
                , th_bpp_ptr
                , th_width_ptr
                , th_height_ptr
                );
  }

  return (th_data);

}
