cb_enable(GtkWidget *button, NetMon *net)
	{
	enable_in_progress = TRUE;
	net->enabled = GTK_TOGGLE_BUTTON(button)->active;
	if (net->force_button)
		{
		if (net->enabled)
			gtk_widget_set_sensitive(net->force_button, TRUE);
		else
			{
			gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(net->force_button),
						FALSE);
			gtk_widget_set_sensitive(net->force_button, FALSE);
			net->force_up = FALSE;
			}
		}
	gtk_widget_set_sensitive(net->alert_button, net->enabled);
	if (net == net_timed && !net->enabled && timer_iface_combo_box)
		gtk_combo_box_set_active(GTK_COMBO_BOX(timer_iface_combo_box), 0);
	else
		sync_chart(net);
	enable_in_progress = FALSE;
	net_spacer_visibility();
	}
