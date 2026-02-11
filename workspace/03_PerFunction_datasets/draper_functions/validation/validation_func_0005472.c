_uniconify_hook(void *data __UNUSED__, int type __UNUSED__, E_Event_Border_Uniconify *event)
{
    E_Border *bd = event->border;
    int stack = -1;

    if (_G.input_mode != INPUT_MODE_NONE
    &&  _G.input_mode != INPUT_MODE_MOVING
    &&  _G.input_mode != INPUT_MODE_TRANSITION)
    {
        end_special_input();
    }

    if (bd->deskshow)
        return true;

    check_tinfo(bd->desk);
    if (!_G.tinfo->conf || !_G.tinfo->conf->nb_stacks) {
        return true;
    }

    if (!is_tilable(bd)) {
        return true;
    }

    stack = get_stack(bd);
    if (stack >= 0) {
        return true;
    }
    _add_border(bd);

    return true;
}
