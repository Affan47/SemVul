prefs_set_spinbtn(PrefParam *pparam)
{
	cm_return_if_fail(*pparam->widget != NULL);

	switch (pparam->type) {
	case P_INT:
		gtk_spin_button_set_value(GTK_SPIN_BUTTON(*pparam->widget),
					  (gfloat)*((gint *)pparam->data));
		break;
	case P_USHORT:
		gtk_spin_button_set_value(GTK_SPIN_BUTTON(*pparam->widget),
					  (gfloat)*((gushort *)pparam->data));
		break;
	default:
		g_warning("Invalid PrefType for GtkSpinButton widget: %d\n",
			  pparam->type);
	}
}
