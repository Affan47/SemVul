study_copy_in_place(AmitkObject * dest_object, const AmitkObject * src_object) {

  AmitkStudy * dest_study;
  AmitkView i_view;

  g_return_if_fail(AMITK_IS_STUDY(src_object));
  g_return_if_fail(AMITK_IS_STUDY(dest_object));

  dest_study = AMITK_STUDY(dest_object);

  amitk_study_set_creation_date(dest_study, AMITK_STUDY_CREATION_DATE(src_object));
  dest_study->view_center = AMITK_STUDY(src_object)->view_center;
  amitk_study_set_view_thickness(dest_study, AMITK_STUDY_VIEW_THICKNESS(src_object));
  dest_study->view_start_time = AMITK_STUDY_VIEW_START_TIME(src_object);
  dest_study->view_duration = AMITK_STUDY_VIEW_DURATION(src_object);
  dest_study->zoom = AMITK_STUDY_ZOOM(src_object);
  dest_study->fov = AMITK_STUDY_FOV(src_object);
  dest_study->fuse_type = AMITK_STUDY_FUSE_TYPE(src_object);
  dest_study->view_mode = AMITK_STUDY_VIEW_MODE(src_object);
  dest_study->canvas_target = AMITK_STUDY_CANVAS_TARGET(src_object);
  for (i_view=0; i_view<AMITK_VIEW_NUM; i_view++)
    dest_study->canvas_visible[i_view] = AMITK_STUDY_CANVAS_VISIBLE(src_object, i_view);


  dest_study->canvas_roi_width = AMITK_STUDY_CANVAS_ROI_WIDTH(src_object);
#ifdef AMIDE_LIBGNOMECANVAS_AA
  dest_study->canvas_roi_transparency = AMITK_STUDY_CANVAS_ROI_TRANSPARENCY(src_object);
#else
  dest_study->canvas_line_style = AMITK_STUDY_CANVAS_LINE_STYLE(src_object);
  dest_study->canvas_fill_roi = AMITK_STUDY_CANVAS_FILL_ROI(src_object);
#endif
  dest_study->canvas_layout = AMITK_STUDY_CANVAS_LAYOUT(src_object);
  dest_study->canvas_maintain_size = AMITK_STUDY_CANVAS_MAINTAIN_SIZE(src_object);
  dest_study->canvas_target_empty_area = AMITK_STUDY_CANVAS_TARGET_EMPTY_AREA(src_object);
  dest_study->panel_layout = AMITK_STUDY_PANEL_LAYOUT(src_object);


  amitk_line_profile_copy_in_place(dest_study->line_profile, AMITK_STUDY_LINE_PROFILE(src_object));


  amitk_study_set_filename(dest_study, AMITK_STUDY_FILENAME(src_object));

  AMITK_OBJECT_CLASS (parent_class)->object_copy_in_place (dest_object, src_object);
}
