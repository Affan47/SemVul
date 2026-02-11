GB_INFO(const char *key, void **value)
	{
		if (!strcasecmp(key, "DISPLAY"))
		{
			#ifdef GDK_WINDOWING_X11
			#ifndef GAMBAS_DIRECTFB
			*value = (void *)gdk_x11_display_get_xdisplay(gdk_display_get_default());
			#else

			*value=0;
			stub("DIRECTFB/EXPORT GB_INFO");
			#endif
			#else

			*value=0;
			stub("no-X11/EXPORT GB_INFO");
			#endif
			return TRUE;
		}
		else if (!strcasecmp(key, "ROOT_WINDOW"))
		{
			#ifdef GDK_WINDOWING_X11
			#ifndef GAMBAS_DIRECTFB
			*value = (void *)gdk_x11_get_default_root_xwindow();
			#else

			*value=0;
			stub("DIRECTFB/EXPORT GB_INFO");
			#endif
			#else

			*value=0;
			stub("no-X11/EXPORT GB_INFO");
			#endif
			return TRUE;
		}
		else
			return FALSE;
	}
}
