uih_slowdowntimers(uih_context * c, int time)
{
    tl_slowdown_timer(c->maintimer, time);
    if (c->autopilot)
	tl_slowdown_timer(c->autopilottimer, time);
    if (c->play) {
	tl_slowdown_timer(c->playc->timer, time);
	if (c->cycling)
	    tl_slowdown_timer(c->cyclingtimer, time);
    }
    if (c->save) {
	tl_slowdown_timer(c->savec->timer, time);
	tl_slowdown_timer(c->savec->synctimer, time);
	if (c->cycling)
	    tl_slowdown_timer(c->cyclingtimer, time);
    }
}
