did_set_title (
    int icon
)
{
  if (starting != NO_SCREEN) {
    maketitle();
    if (icon) {
      if (!p_icon) {
        ui_set_icon(NULL);
      }
    } else {
      if (!p_title) {
        ui_set_title(NULL);
      }
    }
  }
}
