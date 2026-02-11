show_warning(PROJECT* p, char* name) {
    msg_printf(p, MSG_USER_ALERT,
        "Your app_config.xml file refers to an unknown application '%s'.  Known applications: %s",
        name, app_list_string(p).c_str()
    );
}
