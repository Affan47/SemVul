ccss_end_selector (CRDocHandler * a_handler, CRSelector * a_selector_list)
{
    CSSUserData *user_data;

    g_return_if_fail (a_handler);

    user_data = (CSSUserData *) a_handler->app_data;

    cr_selector_unref (user_data->selector);
    user_data->selector = NULL;
}
