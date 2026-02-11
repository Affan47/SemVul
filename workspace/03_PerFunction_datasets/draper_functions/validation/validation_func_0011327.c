delay_until_date_changed_cb (GtkWidget *dedit,
                             gpointer data)
{
	ESendOptionsDialog *sod;
	ESendOptionsDialogPrivate *priv;
	time_t tmp, current;

	sod = data;
	priv = sod->priv;

	current = time (NULL);
	tmp = e_date_edit_get_time (E_DATE_EDIT (priv->delay_until));

	if ((difftime (tmp, current) < 0) || !e_date_edit_time_is_valid (E_DATE_EDIT (priv->delay_until))
					  || !e_date_edit_date_is_valid (E_DATE_EDIT (priv->delay_until)))
		e_date_edit_set_time (E_DATE_EDIT (priv->delay_until), 0);

}
