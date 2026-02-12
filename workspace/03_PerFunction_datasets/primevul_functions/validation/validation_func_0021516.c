get_rx_buf( struct net_device  *dev )
{

	struct sk_buff  *skb = dev_alloc_skb( ETHER_MAX_LEN + 2 );
	if( !skb )
		return  NULL;

	skb_reserve( skb, 2 );
	return  skb;
}
