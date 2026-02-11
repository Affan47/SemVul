iptrack_delete_pid(const pid_t pid)
{
    unsigned int c = 0U;

    if (iptrack_list == NULL) {
        return;
    }
    do {
        if (iptrack_list[c].pid == pid) {
            iptrack_list[c].pid = (pid_t) 0;
            return;
        }
        c++;
    } while (c < maxusers);
}
