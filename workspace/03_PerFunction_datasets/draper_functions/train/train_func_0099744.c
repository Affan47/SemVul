on_OK (G_GNUC_UNUSED GtkWidget *widget, Dialog* pBox)
{
	if (pBox->Apply ())
		pBox->Destroy ();
}
