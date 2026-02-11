p_update_position_widgets(GapPlayerMainGlobalParams *gpp)
{
  static gchar time_txt[12];

  if((gint32)GTK_ADJUSTMENT(gpp->framenr_spinbutton_adj)->value != gpp->play_current_framenr)
  {
    gtk_adjustment_set_value( GTK_ADJUSTMENT(gpp->framenr_spinbutton_adj)
                            , (gfloat)gpp->play_current_framenr
                            );
  }
  gap_timeconv_framenr_to_timestr( (gpp->play_current_framenr - gpp->ainfo_ptr->first_frame_nr)
                           , gpp->original_speed
                           , time_txt
                           , sizeof(time_txt)
                           );

  gtk_label_set_text ( GTK_LABEL(gpp->timepos_label), time_txt);
}
