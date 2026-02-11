cb_template_submit(Fl_Return_Button*, void*) {
  Fl_Shared_Image *img = (Fl_Shared_Image *)template_preview->image();
if (img) img->release();
template_preview->image(0);

template_panel->hide();
}
