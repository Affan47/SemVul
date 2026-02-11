icp_a106_hbar(Driver *drvthis, int x, int y, int len, int promille, int options)
{
  int total_pixels  = ((long) 2 * len * LCD_DEFAULT_CELLWIDTH + 1 ) * promille / 2000;
  int pos;

  for (pos = 0; pos < len; pos ++) {
    int pixels = total_pixels - LCD_DEFAULT_CELLWIDTH * pos;

    if (pixels >= LCD_DEFAULT_CELLWIDTH) {

      icp_a106_icon(drvthis, x+pos, y, ICON_BLOCK_FILLED);
    }
    else if (pixels > 0) {

      icp_a106_chr(drvthis, x+pos, y, '|');
      break;
    }
    else {
      ;
    }
  }
}
