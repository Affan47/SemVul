layout_image_setup_split_common(LayoutWindow *lw, gint n)
{
	gboolean frame = (n > 1) || (!lw->options.tools_float && !lw->options.tools_hidden);
	gint i;

	for (i = 0; i < n; i++)
		if (!lw->split_images[i])
			{
			FileData *img_fd = NULL;
			double zoom = 0.0;

			layout_image_new(lw, i);
			image_set_frame(lw->split_images[i], frame);
			image_set_selectable(lw->split_images[i], (n > 1));

			if (lw->image)
				{
				image_osd_copy_status(lw->image, lw->split_images[i]);
				}

			if (layout_selection_count(lw, 0) > 1)
				{
				GList *work = g_list_last(layout_selection_list(lw));
				gint j = 0;

				if (work) work = work->prev;

				while (work && j < i)
					{
					FileData *fd = work->data;
					work = work->prev;

					j++;
					if (!fd || !*fd->path) continue;
					img_fd = fd;
					}
				}

			if (!img_fd && lw->image)
				{
				img_fd = image_get_fd(lw->image);
				zoom = image_zoom_get(lw->image);
				}

			if (img_fd)
				{
				gdouble sx, sy;
				image_change_fd(lw->split_images[i], img_fd, zoom);
				image_get_scroll_center(lw->image, &sx, &sy);
				image_set_scroll_center(lw->split_images[i], sx, sy);
				}
			layout_image_deactivate(lw, i);
			}
		else
			{
			image_set_frame(lw->split_images[i], frame);
			image_set_selectable(lw->split_images[i], (n > 1));
			}

	for (i = n; i < MAX_SPLIT_IMAGES; i++)
		{
		if (lw->split_images[i])
			{
#if GTK_CHECK_VERSION(2,12,0)
			g_object_unref(lw->split_images[i]->widget);
#else
			gtk_widget_unref(lw->split_images[i]->widget);
#endif
			lw->split_images[i] = NULL;
			}
		}

	if (!lw->image || lw->active_split_image < 0 || lw->active_split_image >= n)
		{
		layout_image_activate(lw, 0, TRUE);
		}
	else
		{


		layout_image_activate(lw, lw->active_split_image, TRUE);
		}
}
