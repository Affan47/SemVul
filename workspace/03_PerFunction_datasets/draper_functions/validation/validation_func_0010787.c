action_handle_menu(event_t *ev, action_t *action)
{
    REQUIRE_RVAL(action->param.menu != NULL, 0);
    menu_invoke(ev->xbutton.x, ev->xbutton.y, TermWin.parent, action->param.menu, ev->xbutton.time);
    return 1;
}
