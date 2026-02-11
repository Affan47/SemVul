gsb_automem_spin_button_changed ( GtkWidget *spin,
						  gpointer null)
{
    gint *data;

    data = g_object_get_data ( G_OBJECT(spin), "pointer" );

    if ( data )
    {
	*data = gtk_spin_button_get_value_as_int ( GTK_SPIN_BUTTON(spin));
	if ( etat.modification_fichier == 0 )
        modification_fichier ( TRUE );
    }

    return (FALSE);
}
