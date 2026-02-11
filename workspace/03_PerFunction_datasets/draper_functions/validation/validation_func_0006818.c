aisc_remove_destroy_callback() {

    struct Socinf  *si;
    int             socket = aisc_server_con;
    struct Hs_struct *hs = aisc_server_hs;
    if (!hs)
        return;
    for (si = hs->soci; si; si = si->next) {
        if (si->socket == socket) {
            si->destroy_callback = 0;
            si->destroy_clientdata = 0;
        }
    }
}
