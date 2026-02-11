aisc_init_client( aisc_com *link )
{
    int len,mes_cnt;
    mes_cnt = 2;
    link->aisc_mes_buffer[0] = mes_cnt-2;
    link->aisc_mes_buffer[1] = AISC_INIT+link->magic;
    len = aisc_c_write(link->socket, (char *)(link->aisc_mes_buffer), mes_cnt * sizeof(long));
    if (!len) {
        link->error = err_connection_problems;
        PRTERR("AISC_CONN_ERROR");
        return 0;
    }
    aisc_check_error(link);
    return (void *)(link->aisc_mes_buffer[0]);
}
