_transition_overlays_free_cb(void *data)
{
    transition_overlay_t *trov = data;

    if (trov->overlay.obj) {
        evas_object_del(trov->overlay.obj);
        trov->overlay.obj = NULL;
    }
    if (trov->overlay.popup) {
        e_object_del(E_OBJECT(trov->overlay.popup));
        trov->overlay.popup = NULL;
    }
    if (trov != _G.transition_overlay) {
        E_FREE(trov);
    }
}
