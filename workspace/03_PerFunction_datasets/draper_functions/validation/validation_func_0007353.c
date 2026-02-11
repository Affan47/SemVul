LoadFont (char *filename, float scale)
{
  SDL_Surface *surface = NULL;
  int x;
  BFont_Info *Font = NULL;

  if (filename != NULL)
    {
      Font = (BFont_Info *) MyMalloc (sizeof (BFont_Info));
      if (Font != NULL)
	{
	  surface = (SDL_Surface *) IMG_Load (filename);
	  ScalePic (&surface, scale);

	  if (surface != NULL)
	    {
	      Font->Surface = surface;
	      for (x = 0; x < 256; x++)
		{
		  Font->Chars[x].x = 0;
		  Font->Chars[x].y = 0;
		  Font->Chars[x].h = 0;
		  Font->Chars[x].w = 0;
		}

	      InitFont (Font);

	      SetCurrentFont (Font);
	    }
	  else
	    {

	      free (Font);
	      Font = NULL;
	    }
	}
    }

  return Font;
}
