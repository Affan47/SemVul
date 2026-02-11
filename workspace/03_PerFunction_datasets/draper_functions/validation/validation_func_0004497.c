net80211_set_rtscts_rate ( struct net80211_device *dev )
{
	u16 datarate = dev->rates[dev->rate];
	u16 rtsrate = 0;
	int rts_idx = -1;
	int i;

	for ( i = 0; i < dev->nr_rates; i++ ) {
		u16 rate = dev->rates[i];

		if ( ! ( dev->basic_rates & ( 1 << i ) ) || rate > datarate )
			continue;

		if ( rate > rtsrate ) {
			rtsrate = rate;
			rts_idx = i;
		}
	}


	if ( rts_idx < 0 )
		rts_idx = 0;

	dev->rtscts_rate = rts_idx;
}
