ExecSeqStat6 (
    Stat                stat )
{
    UInt                leave;


    if ( (leave = EXEC_STAT( ADDR_STAT(stat)[0] )) != 0 ) { return leave; }
    if ( (leave = EXEC_STAT( ADDR_STAT(stat)[1] )) != 0 ) { return leave; }
    if ( (leave = EXEC_STAT( ADDR_STAT(stat)[2] )) != 0 ) { return leave; }
    if ( (leave = EXEC_STAT( ADDR_STAT(stat)[3] )) != 0 ) { return leave; }
    if ( (leave = EXEC_STAT( ADDR_STAT(stat)[4] )) != 0 ) { return leave; }


    return EXEC_STAT( ADDR_STAT(stat)[5] );
}
