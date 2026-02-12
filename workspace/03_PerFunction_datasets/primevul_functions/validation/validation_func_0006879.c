parse_WRITE_ACTIONS(char *arg, const struct ofpact_parse_params *pp)
{
    size_t ofs = ofpacts_pull(pp->ofpacts);
    struct ofpact_nest *on;
    char *error;


    ofpact_put(pp->ofpacts, OFPACT_WRITE_ACTIONS, sizeof *on);
    ofpbuf_pull(pp->ofpacts, sizeof *on);


    error = ofpacts_parse(arg, pp, false, OFPACT_WRITE_ACTIONS);


    on = ofpbuf_push_uninit(pp->ofpacts, sizeof *on);
    on->ofpact.len = pp->ofpacts->size;


    ofpbuf_push_uninit(pp->ofpacts, ofs);

    return error;
}
