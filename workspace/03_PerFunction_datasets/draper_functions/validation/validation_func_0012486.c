gst_video_box_recalc_transform (GstVideoBox * video_box)
{
  gboolean res = TRUE;


  if (video_box->in_format == video_box->out_format &&
      video_box->box_left == 0 && video_box->box_right == 0 &&
      video_box->box_top == 0 && video_box->box_bottom == 0 &&
      video_box->in_sdtv == video_box->out_sdtv) {

    GST_LOG_OBJECT (video_box, "we are using passthrough");
    gst_base_transform_set_passthrough (GST_BASE_TRANSFORM_CAST (video_box),
        TRUE);
  } else {
    GST_LOG_OBJECT (video_box, "we are not using passthrough");
    gst_base_transform_set_passthrough (GST_BASE_TRANSFORM_CAST (video_box),
        FALSE);
  }
  return res;
}
