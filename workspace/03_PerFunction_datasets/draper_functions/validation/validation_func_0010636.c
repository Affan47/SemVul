gscrollbar_destroy(GGadget *g) {
    GScrollBar *gsb = (GScrollBar *) g;

    if ( gsb==NULL )
return;
    GDrawCancelTimer(gsb->pressed);
    _ggadget_destroy(g);
}
