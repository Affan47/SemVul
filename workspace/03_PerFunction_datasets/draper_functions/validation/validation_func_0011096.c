Load_Block (char *fpath, int line, int col, SDL_Rect * block, int flags)
{
  static SDL_Surface *pic = NULL;
  SDL_Surface *tmp;
  SDL_Rect src, dim;
  SDL_Surface *ret;
  int usealpha;

  if (!fpath && !pic)
    return (NULL);

  if (fpath)
    {
      if (pic)
	SDL_FreeSurface (pic);
      pic = IMG_Load (fpath);

    }

  if ( (flags & INIT_ONLY) != FALSE )
    return (NULL);

  if (!block)
    {
      Set_Rect (dim, 0, 0, pic->w, pic->h);
    }
  else
    {
      Set_Rect (dim, 0, 0, block->w, block->h);
    }

  if (pic->format->Amask != 0)
    usealpha = TRUE;
  else
    usealpha = FALSE;

  if (usealpha)
    SDL_SetAlpha (pic, 0, 0);
  tmp = SDL_CreateRGBSurface (0, dim.w, dim.h, vid_bpp, 0, 0, 0, 0);
  if (usealpha)
    ret = SDL_DisplayFormatAlpha (tmp);
  else
    ret = SDL_DisplayFormat (tmp);
  SDL_FreeSurface (tmp);

  Set_Rect (src, col * (dim.w + 2), line * (dim.h + 2), dim.w, dim.h);
  SDL_BlitSurface (pic, &src, ret, NULL);
  if (usealpha)
    SDL_SetAlpha (ret, SDL_SRCALPHA | SDL_RLEACCEL, SDL_ALPHA_OPAQUE);

  return (ret);

}
