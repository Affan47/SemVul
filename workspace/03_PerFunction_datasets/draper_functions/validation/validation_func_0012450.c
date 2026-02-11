is_skip(Window w)
{
    Atom win_type, state;
    int i;
    unsigned long r;

    if (get_atoms(w, net_wm_wintype, XA_ATOM, 0, &win_type, 1, NULL) &&
            (win_type == net_wm_type_dock || win_type == net_wm_type_desk))
        return 1;

    for (i = 0, r = 1; r; i += r)
        if ((r = get_atoms(w, net_wm_state, XA_ATOM, i, &state, 1, NULL)) &&
                (state == net_wm_state_skipt || state == net_wm_state_skipp))
            return 1;

    return 0;
}
