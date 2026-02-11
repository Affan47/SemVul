spd_sound_icon(int connection, SPDPriority priority, const char *icon_name)
{
    char *command;
    int ret;

    if (icon_name == NULL) return -1;

    ret = spd__set_priority(connection, priority);
    if (ret) return -1;

    command = g_strdup_printf("SOUND_ICON %s", icon_name);
    ret = spd_execute_command(connection, command);
    spd__free (command);
    if (ret) return -1;

    return 0;
}
