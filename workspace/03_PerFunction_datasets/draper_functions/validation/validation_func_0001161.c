draw_wait()
{
  if (seq[423].frame[8] != 0)
    {

      if (please_wait)
	{
	  SDL_Rect dst = {232, 0, GFX_k[seq[423].frame[7]].k->w, GFX_k[seq[423].frame[7]].k->h};
	  SDL_BlitSurface(GFX_k[seq[423].frame[7]].k, NULL, GFX_lpDDSBack, &dst);
	  SDL_UpdateRects(GFX_lpDDSBack, 1, &dst);
	  please_wait = 0;
	}
      else
	{
	  SDL_Rect dst = {232, 0, GFX_k[seq[423].frame[8]].k->w, GFX_k[seq[423].frame[8]].k->h};
	  SDL_BlitSurface(GFX_k[seq[423].frame[8]].k, NULL, GFX_lpDDSBack, &dst);
	  SDL_UpdateRects(GFX_lpDDSBack, 1, &dst);
	  please_wait = 1;
	}
    }
}
