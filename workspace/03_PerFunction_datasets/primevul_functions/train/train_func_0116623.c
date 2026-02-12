bool unit_stop_pending(Unit *u) {
        assert(u);


        return u->job && u->job->type == JOB_STOP;
}
