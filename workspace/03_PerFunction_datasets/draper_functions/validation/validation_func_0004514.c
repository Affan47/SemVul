magick_exists(EnvT *e)
  {
#ifdef USE_MAGICK
    return new DIntGDL(1);
#else
    return new DIntGDL(0);
#endif
  }
