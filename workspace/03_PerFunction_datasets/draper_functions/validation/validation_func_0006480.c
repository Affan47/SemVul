dialog_response (GtkWidget * widget, gint response, gftp_dialog_data * ddata)
{
  if (ddata->edit == NULL)
    {
      gtk_widget_destroy (ddata->dialog);
      ddata->dialog = NULL;
      ddata->checkbox = NULL;
    }

  switch (response)
    {
      case GTK_RESPONSE_YES:
        if (ddata->yesfunc != NULL)
          ddata->yesfunc (ddata->yespointer, ddata);
        break;
      default:
        if (ddata->nofunc != NULL)
          ddata->nofunc (ddata->nopointer, ddata);
        break;
    }

  if (ddata->edit != NULL &&
      ddata->dialog != NULL)
    gtk_widget_destroy (ddata->dialog);

  g_free (ddata);
}
