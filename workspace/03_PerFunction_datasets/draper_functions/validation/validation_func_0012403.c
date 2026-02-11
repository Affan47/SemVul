GDrawSetClip(GWindow w, GRect *rct) {
    if ( rct==NULL ) {
	w->ggc->clip.x = w->ggc->clip.y = 0;
	w->ggc->clip.width = w->ggc->clip.height = 0x7fff;
    } else
	w->ggc->clip = *rct;
}
