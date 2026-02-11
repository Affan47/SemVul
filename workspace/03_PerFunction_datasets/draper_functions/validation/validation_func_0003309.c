add_ring_trust( CTX c, PACKET *pkt )
{
    if( !c->list ) {
	log_error("ring trust w/o key\n" );
	return 0;
    }
    add_kbnode( c->list, new_kbnode( pkt ) );
    return 1;
}
