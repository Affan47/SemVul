on_mw__button_vrange_docked_clicked             (GtkButton       *button,
                                                 GapVexMainGlobalParams *gpp)
{
 gdouble delace;

 delace = gpp->val.deinterlace;
 if(delace == GAP_VEX_DELACE_ODD_X2)
 {
   delace = GAP_VEX_DELACE_ODD;
 }
 if(delace == GAP_VEX_DELACE_EVEN_X2)
 {
   delace = GAP_VEX_DELACE_EVEN;
 }
 delace += CLAMP(gpp->val.delace_threshold, 0.0, 0.9999);


 if(gap_debug) printf("CB: on_mw__button_vrange_docked_clicked\n");
 if(gpp == NULL) return;

 p_call_player_widget(gpp
                   ,gpp->val.videoname
                   ,gpp->video_width
                   ,gpp->video_height
                   , gpp->val.begin_frame
                   , gpp->val.end_frame
                   , gpp->val.videotrack
                   , delace
                   , TRUE
                   );
}
