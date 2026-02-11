osm_gps_map_draw (GtkWidget *widget, cairo_t *cr)
{
    OsmGpsMap *map = OSM_GPS_MAP(widget);
    OsmGpsMapPrivate *priv = map->priv;

    if (!priv->drag_mouse_dx && !priv->drag_mouse_dy) {
        cairo_set_source_surface (cr, priv->pixmap, 0, 0);
    } else {
        cairo_set_source_surface (cr, priv->pixmap,
            priv->drag_mouse_dx - EXTRA_BORDER,
            priv->drag_mouse_dy - EXTRA_BORDER);
    }

    cairo_paint (cr);

    if (priv->layers) {
        GSList *list;
        for(list = priv->layers; list != NULL; list = list->next) {
            OsmGpsMapLayer *layer = list->data;
            osm_gps_map_layer_draw(layer, map, cr);
        }
    }

    return FALSE;
}
