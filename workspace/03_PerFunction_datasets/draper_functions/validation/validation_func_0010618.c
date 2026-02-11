net80211_rx ( struct net80211_device *dev, struct io_buffer *iob,
		   int signal, u16 rate )
{
	struct ieee80211_frame *hdr = iob->data;
	u16 type = hdr->fc & IEEE80211_FC_TYPE;
	if ( ( hdr->fc & IEEE80211_FC_VERSION ) != IEEE80211_THIS_VERSION )
		goto drop;

	if ( type == IEEE80211_TYPE_CTRL )
		goto drop;


	if ( dev->last_rx_seq == hdr->seq )
		goto drop;
	dev->last_rx_seq = hdr->seq;

	if ( dev->hw->flags & NET80211_HW_RX_HAS_FCS ) {

		iob_unput ( iob, 4 );
	}


	if ( ( hdr->fc & IEEE80211_FC_PROTECTED ) &&
	     ! memcmp ( hdr->addr2, dev->bssid, ETH_ALEN ) ) {

		struct io_buffer *niob;
		struct net80211_crypto *crypto = dev->crypto;

		if ( ! dev->crypto ) {
			DBGC ( dev, "802.11 %p cannot decrypt packet "
			       "without a cryptosystem\n", dev );
			goto drop_crypt;
		}

		if ( ( hdr->addr1[0] & 1 ) && dev->gcrypto ) {

			crypto = dev->gcrypto;
		}

		niob = crypto->decrypt ( crypto, iob );
		if ( ! niob ) {
			DBGC ( dev, "802.11 %p decryption error\n", dev );
			goto drop_crypt;
		}
		free_iob ( iob );
		iob = niob;
		hdr = iob->data;
	}

	dev->last_signal = signal;


	if ( IEEE80211_FRAG ( hdr->seq ) != 0
	     || ( hdr->fc & IEEE80211_FC_MORE_FRAG ) ) {
		net80211_rx_frag ( dev, iob, signal );
		return;
	}


	if ( type == IEEE80211_TYPE_MGMT ) {
		net80211_handle_mgmt ( dev, iob, signal );
		return;
	}


	if ( ( hdr->fc & IEEE80211_FC_SUBTYPE ) != IEEE80211_STYPE_DATA )
		goto drop;


	if ( dev->rctl )
		rc80211_update_rx ( dev, hdr->fc & IEEE80211_FC_RETRY, rate );


	if ( dev->state & NET80211_ASSOCIATED ) {
		netdev_rx ( dev->netdev, iob );
		return;
	}


	goto drop;

 drop_crypt:
	netdev_rx_err ( dev->netdev, NULL, EINVAL_CRYPTO_REQUEST );
 drop:
	DBGC2 ( dev, "802.11 %p dropped packet fc=%04x seq=%04x\n", dev,
		hdr->fc, hdr->seq );
	free_iob ( iob );
	return;
}
