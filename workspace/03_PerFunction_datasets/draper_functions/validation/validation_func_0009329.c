wap_push_ppg_pushuser_client_phone_number_acceptable(Octstr *username,
        Octstr *number)
{
    WAPPushUser *u;

    u = user_find_by_username(username);
    if (!prefix_allowed(u, number)) {
        error(0, "Number %s not allowed by user %s (wrong prefix)",
              octstr_get_cstr(number), octstr_get_cstr(username));
        return 0;
    }

    if (blacklisted(u, number)) {
        error(0, "Number %s not allowed by user %s (blacklisted)",
              octstr_get_cstr(number), octstr_get_cstr(username) );
        return 0;
    }

    if (!whitelisted(u, number)) {
        error(0, "Number %s not allowed by user %s (not whitelisted)",
              octstr_get_cstr(number), octstr_get_cstr(username) );
        return 0;
    }

    return 1;
}
