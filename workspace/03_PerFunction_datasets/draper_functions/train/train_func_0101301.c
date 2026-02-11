_clarity_widget_unrealized_cb(GtkWidget *widget, gpointer data) {
    if (! CLARITY_IS_WIDGET(widget))
        return;

    ClarityWidget *cw = CLARITY_WIDGET(widget);
    ClarityWidgetPrivate *priv = CLARITY_WIDGET_GET_PRIVATE (cw);

    if (priv->draw_area == NULL)
        return;


    if (GTK_IS_WIDGET(priv->draw_area)) {
        gtk_widget_destroy(priv->draw_area);
        priv->draw_area = NULL;
    }
}
