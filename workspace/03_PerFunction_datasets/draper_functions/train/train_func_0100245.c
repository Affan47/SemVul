focus_fallback_target(gboolean allow_refocus,
                                       gboolean allow_pointer,
                                       gboolean allow_omnipresent,
                                       ObClient *old)
{
    GList *it;
    ObClient *c;

    ob_debug_type(OB_DEBUG_FOCUS, "trying pointer stuff");
    if (allow_pointer && config_focus_follow)
        if ((c = client_under_pointer()) &&
            (allow_refocus || client_focus_target(c) != old) &&
            (client_normal(c) &&
             client_focus(c)))
        {
            ob_debug_type(OB_DEBUG_FOCUS, "found in pointer stuff");
            return c;
        }

    ob_debug_type(OB_DEBUG_FOCUS, "trying the focus order");
    for (it = focus_order; it; it = g_list_next(it)) {
        c = it->data;


        if ((allow_omnipresent || c->desktop == screen_desktop) &&
            focus_valid_target(c, screen_desktop,
                               TRUE, FALSE, FALSE, TRUE, FALSE, FALSE,
                               FALSE) &&
            !c->shaded &&
            (allow_refocus || client_focus_target(c) != old) &&
            client_focus(c))
        {
            ob_debug_type(OB_DEBUG_FOCUS, "found in focus order");
            return c;
        }
    }

    ob_debug_type(OB_DEBUG_FOCUS, "trying a desktop window");
    for (it = focus_order; it; it = g_list_next(it)) {
        c = it->data;


        if (focus_valid_target(c, screen_desktop,
                               TRUE, FALSE, FALSE, TRUE, FALSE, TRUE, FALSE) &&
            (allow_refocus || client_focus_target(c) != old) &&
            client_focus(c))
        {
            ob_debug_type(OB_DEBUG_FOCUS, "found a desktop window");
            return c;
        }
    }

    return NULL;
}
