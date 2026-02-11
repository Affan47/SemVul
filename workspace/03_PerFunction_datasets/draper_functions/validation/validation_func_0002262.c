ar5416GetTsf64(struct ath_hal *ah)
{
	a_uint32_t tsf_lower, tsf_upper1, tsf_upper2;
	a_int32_t i;

	tsf_upper1 = ioread32_mac(AR_TSF_U32);
	for (i = 0; i < ATH9K_HTC_MAX_TSF_READ; i++) {
		tsf_lower = ioread32_mac(AR_TSF_L32);
		tsf_upper2 = ioread32_mac(AR_TSF_U32);
		if (tsf_upper2 == tsf_upper1)
			break;
		tsf_upper1 = tsf_upper2;
	}

	return (((u_int64_t)tsf_upper2 << 32) | tsf_lower);
}
