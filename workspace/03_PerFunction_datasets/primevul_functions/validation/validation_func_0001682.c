static gdFontPtr php_find_gd_font(int size) {
  gdFontPtr font;

  switch (size) {
  case 1:
    font = gdFontTiny;
    break;
  case 2:
    font = gdFontSmall;
    break;
  case 3:
    font = gdFontMediumBold;
    break;
  case 4:
    font = gdFontLarge;
    break;
  case 5:
    font = gdFontGiant;
    break;
  default:
    raise_warning("Unsupported font: %d", size);


    if (size < 1) {
      font = gdFontTiny;
    } else {
      font = gdFontGiant;
    }
    break;
  }
  return font;
}
