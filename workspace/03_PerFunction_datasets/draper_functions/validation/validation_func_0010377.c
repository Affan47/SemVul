restore_colors_after_printing()
{
  int i;

  backgroundcolor = backup_color_1;
  small_ruler_color = backup_color_2;
  big_ruler_color = backup_color_3;
  mouse_rect_color = backup_color_4;
  text_color = backup_color_5;
  floating_ruler_color = backup_color_14;

  for(i=0; i<mainwindow->signalcomps; i++)
  {
    mainwindow->signalcomp[i]->color = backup_color_10[i];
  }
  crosshair_1.color = backup_color_11;
  crosshair_2.color = backup_color_12;
  baseline_color = backup_color_13;
  annot_marker_color = backup_color_15;
}
