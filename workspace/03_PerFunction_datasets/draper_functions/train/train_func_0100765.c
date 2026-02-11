cddb_disc_add_track(cddb_disc_t *disc, cddb_track_t *track)
{
    cddb_log_debug("cddb_disc_add_track()");
    if (!disc->tracks) {

        disc->tracks = track;
    } else {

        cddb_track_t *t;

        t = disc->tracks;
        while (t->next) {
            t = t->next;
        }
        t->next = track;
        track->prev = t;
    }
    disc->track_cnt++;
    track->num = disc->track_cnt;
    track->disc = disc;
}
