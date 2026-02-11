checkargs (int argc, char **argv, bool_t *double_resolution, bool_t *panel,
	   int *fps, char **image_name, fiasco_d_options_t **options)


{
   int optind;

   optind = parseargs (params, argc, argv,
		       "Decode FIASCO-FILEs and write frame(s) to disk.",
		       "With no FIASCO-FILE, or if FIASCO-FILE is -, "
		       "read standard input.\n"
		       "Environment:\n"
		       "FIASCO_DATA   Search path for automata files. "
		       "Default: ./\n"
		       "FIASCO_IMAGES Save path for image files. "
		       "Default: ./", " [FIASCO-FILE]...",
		       FIASCO_SHARE, "system.fiascorc", ".fiascorc");

   *image_name        =   (char *)   parameter_value (params, "output");
   *double_resolution = *((bool_t *) parameter_value (params, "double"));
   *panel             = *((bool_t *) parameter_value (params, "panel"));
   *fps		      = *((int *)    parameter_value (params, "framerate"));


   *options = fiasco_d_options_new ();

   {
      int n = *((int *) parameter_value (params, "smoothing"));

      if (!fiasco_d_options_set_smoothing (*options, max (-1, n)))
	 error (fiasco_get_error_message ());
   }

   {
      int n = *((int *) parameter_value (params, "magnify"));

      if (!fiasco_d_options_set_magnification (*options, n))
	 error (fiasco_get_error_message ());
   }

   {
      bool_t n = *((bool_t *) parameter_value (params, "fast"));

      if (!fiasco_d_options_set_4_2_0_format (*options, n > 0 ? YES : NO))
	 error (fiasco_get_error_message ());
   }

   return optind;
}
