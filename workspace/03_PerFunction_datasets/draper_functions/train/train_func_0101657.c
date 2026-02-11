fl_hide_command_log( void )
{
    create_logger( );

    if ( logger->cmd->visible )
        fl_hide_form( logger->cmd );
}
