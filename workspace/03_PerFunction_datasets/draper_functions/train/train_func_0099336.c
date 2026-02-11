do_print_stat_pids( struct stat_context *ctx )
{
        struct pidinfo *info_p;

        info_p = ctx->pinfo;
        while ( info_p != NULL ) {
                if ( group_get_size( info_p->grp ) > 0 ) {
                        gui_print_pid_banner( info_p );
                        print_titlebar();
                        gui_print_group( info_p->grp, 0,0 );
                }
                info_p = info_p->next;
        }
}
