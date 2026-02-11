city_dialog_update_citizens(struct city_dialog *pdialog)
{
  enum citizen_category citizens[MAX_CITY_SIZE];
  int i, width, size, xpad;
  struct city *pcity = pdialog->pcity;
  int num_citizens = get_city_citizen_types(pcity, FEELING_FINAL, citizens);


  if (num_citizens > 1) {
    width = MIN(tileset_small_sprite_width(tileset),
		((NUM_CITIZENS_SHOWN - 1) * tileset_small_sprite_width(tileset)) /
		(num_citizens - 1));
  } else {
    width = tileset_small_sprite_width(tileset);
  }
  pdialog->cwidth = width;


  gtk_misc_get_padding(GTK_MISC(pdialog->citizen_pixmap), &xpad, NULL);
  gtk_pixcomm_clear(GTK_PIXCOMM(pdialog->citizen_pixmap));

  size = (num_citizens - 1) * width + tileset_small_sprite_width(tileset) +
         2 * xpad;
  gtk_widget_set_size_request(GTK_WIDGET(pdialog->citizen_pixmap), size, -1);

  for (i = 0; i < num_citizens; i++) {
    gtk_pixcomm_copyto(GTK_PIXCOMM(pdialog->citizen_pixmap),
                       get_citizen_sprite(tileset, citizens[i], i, pcity),
                       i * width, 0);
  }


}
