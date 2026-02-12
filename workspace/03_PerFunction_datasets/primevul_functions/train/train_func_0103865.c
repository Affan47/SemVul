asn_to_calendar	(
	ASN1_TIME *asn1time,
	struct calendar *pjd
	)
{
	size_t	len;
	char	v[24];
	unsigned long	temp;


	len = asn1time->length;
	REQUIRE(len < sizeof(v));
	(void)strncpy(v, (char *)(asn1time->data), len);
	REQUIRE(len >= 13);
	temp = strtoul(v+len-3, NULL, 10);
	pjd->second = temp;
	v[len-3] = '\0';

	temp = strtoul(v+len-5, NULL, 10);
	pjd->minute = temp;
	v[len-5] = '\0';

	temp = strtoul(v+len-7, NULL, 10);
	pjd->hour = temp;
	v[len-7] = '\0';

	temp = strtoul(v+len-9, NULL, 10);
	pjd->monthday = temp;
	v[len-9] = '\0';

	temp = strtoul(v+len-11, NULL, 10);
	pjd->month = temp;
	v[len-11] = '\0';

	temp = strtoul(v, NULL, 10);

	if (temp < 50UL)
	    temp += 100UL;
	if (temp < 150UL)
	    temp += 1900UL;
	pjd->year = temp;

	pjd->yearday = pjd->weekday = 0;
	return;
}
