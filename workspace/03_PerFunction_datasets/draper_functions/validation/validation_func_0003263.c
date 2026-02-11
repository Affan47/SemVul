real_assign_crtcs (GnomeRRScreen *screen,
		   GnomeOutputInfo **outputs,
		   CrtcAssignment *assignment,
		   GError **error)
{
    GnomeRRCrtc **crtcs = gnome_rr_screen_list_crtcs (screen);
    GnomeOutputInfo *output;
    int i;
    gboolean tried_mode;
    GError *my_error;
    GString *accumulated_error;
    gboolean success;

    output = *outputs;
    if (!output)
	return TRUE;


    if (!output->on)
    {
	return real_assign_crtcs (screen, outputs + 1, assignment, error);
    }

    success = FALSE;
    tried_mode = FALSE;
    accumulated_error = g_string_new (NULL);

    for (i = 0; crtcs[i] != NULL; ++i)
    {
	GnomeRRCrtc *crtc = crtcs[i];
	int crtc_id = gnome_rr_crtc_get_id (crtc);
	int pass;

	g_string_append_printf (accumulated_error,
				_("Trying modes for CRTC %d\n"),
				crtc_id);


	for (pass = 0; pass < 2; ++pass)
	{
	    GnomeRROutput *gnome_rr_output = gnome_rr_screen_get_output_by_name (screen, output->name);
	    GnomeRRMode **modes = gnome_rr_output_list_modes (gnome_rr_output);
	    int j;

	    for (j = 0; modes[j] != NULL; ++j)
	    {
		GnomeRRMode *mode = modes[j];
		int mode_width;
		int mode_height;
		int mode_freq;

		mode_width = gnome_rr_mode_get_width (mode);
		mode_height = gnome_rr_mode_get_height (mode);
		mode_freq = gnome_rr_mode_get_freq (mode);

		g_string_append_printf (accumulated_error,
					_("CRTC %d: trying mode %dx%d@%dHz with output at %dx%d@%dHz (pass %d)\n"),
					crtc_id,
					mode_width, mode_height, mode_freq,
					output->width, output->height, output->rate,
					pass);

		if (mode_width == output->width	&&
		    mode_height == output->height &&
		    (pass == 1 || mode_freq == output->rate))
		{
		    tried_mode = TRUE;

		    my_error = NULL;
		    if (crtc_assignment_assign (
			    assignment, crtc, modes[j],
			    output->x, output->y,
			    output->rotation,
                            output->primary,
			    gnome_rr_output,
			    &my_error))
		    {
			my_error = NULL;
			if (real_assign_crtcs (screen, outputs + 1, assignment, &my_error)) {
			    success = TRUE;
			    goto out;
			} else
			    accumulate_error (accumulated_error, my_error);

			crtc_assignment_unassign (assignment, crtc, gnome_rr_output);
		    } else
			accumulate_error (accumulated_error, my_error);
		}
	    }
	}
    }

out:

    if (success)
	g_string_free (accumulated_error, TRUE);
    else {
	char *str;

	str = g_string_free (accumulated_error, FALSE);

	if (tried_mode)
	    g_set_error (error, GNOME_RR_ERROR, GNOME_RR_ERROR_CRTC_ASSIGNMENT,
			 _("could not assign CRTCs to outputs:\n%s"),
			 str);
	else
	    g_set_error (error, GNOME_RR_ERROR, GNOME_RR_ERROR_CRTC_ASSIGNMENT,
			 _("none of the selected modes were compatible with the possible modes:\n%s"),
			 str);

	g_free (str);
    }

    return success;
}
