UpdateBrateTbl(struct adapter *Adapter, u8 *mbrate)
{
	u8	i;
	u8	rate;


	for (i = 0; i < NDIS_802_11_LENGTH_RATES_EX; i++) {
		rate = mbrate[i] & 0x7f;
		switch (rate) {
		case IEEE80211_CCK_RATE_1MB:
		case IEEE80211_CCK_RATE_2MB:
		case IEEE80211_CCK_RATE_5MB:
		case IEEE80211_CCK_RATE_11MB:
		case IEEE80211_OFDM_RATE_6MB:
		case IEEE80211_OFDM_RATE_12MB:
		case IEEE80211_OFDM_RATE_24MB:
			mbrate[i] |= IEEE80211_BASIC_RATE_MASK;
			break;
		}
	}
}
