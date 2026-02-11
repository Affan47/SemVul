request_composer_scene(void)
{
  char *filename;
  time_t time_1, time_2;
  unsigned long nitems, left;
  int format, *ready, ready2;
  Atom type;

  if (TheDisplay == NULL) {
    TheDisplay = XOpenDisplay(NULL);
    GET_COMPOSER_DATA = XInternAtom(TheDisplay,
				    "Get Composer Data", FALSE);
    NAME_OF_COMPOSER_FILE = XInternAtom(TheDisplay,
					"Name of Composer File", FALSE);
    COMPOSER_DATA_READY = XInternAtom(TheDisplay,
				      "Composer Data Ready", FALSE);
  }


  ready2 = COMPOSER_EXPORT_REQUESTED;
  ready = &ready2;
  XChangeProperty(TheDisplay,
		  DefaultRootWindow(TheDisplay),
		  COMPOSER_DATA_READY, XA_INTEGER, 32,
		  PropModeReplace,
		  (unsigned const char *)ready, 1);


  ready2 = TRUE;
  XChangeProperty(TheDisplay,
		  DefaultRootWindow(TheDisplay),
		  GET_COMPOSER_DATA, XA_INTEGER, 32,
		  PropModeReplace,
		  (unsigned const char *)ready, 1);


  time(&time_1);
  while (*ready != COMPOSER_EXPORT_DONE) {
    if (XGetWindowProperty(TheDisplay,
			   DefaultRootWindow(TheDisplay),
			   COMPOSER_DATA_READY, 0, sizeof(int),
			   FALSE, XA_INTEGER, &type, &format,
			   &nitems, &left, (unsigned char **)(&ready))
	!= Success) {
      return NULL;
    }


    time(&time_2);

    if (((long)time_2 - (long)time_1) > (*ready == COMPOSER_EXPORT_SENDING
				    ? TIME_OUT_DONE : TIME_OUT_SEND ))
    {
      printf ("\nUnable to find 'composer'.  Reading from file: ./%s\n",
	      COMPOSER_DEFAULT_EXPORT_NAME);
      return read_scene(COMPOSER_DEFAULT_EXPORT_NAME);
    }
  }


  XGetWindowProperty(TheDisplay,
		     DefaultRootWindow(TheDisplay),
		     NAME_OF_COMPOSER_FILE, 0, PATH_MAX,
		     FALSE, XA_STRING, &type, &format,
		     &nitems, &left, (unsigned char **)(&filename));

  return read_scene(filename);
}
