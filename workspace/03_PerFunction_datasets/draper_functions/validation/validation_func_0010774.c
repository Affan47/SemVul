static_start (gamgi_enum font,
const float **points, const int **driver, FT_Library *freetype,
FT_Face *face, gamgi_extruded **extruded, char *error)
{
if (font > GAMGI_IO_FONTS_WIRED)
  {


  *extruded = static_extruded_create (font, freetype, face, error);
  if (*extruded == NULL) return FALSE;
  }
else
  {


  gamgi_mesa_text_data_wired (font, points, driver);
  }

return TRUE;
}
