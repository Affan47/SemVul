r8712_secgetmic(struct mic_data *pmicdata, u8 *dst)
{

	secmicappendbyte(pmicdata, 0x5a);
	secmicappendbyte(pmicdata, 0);
	secmicappendbyte(pmicdata, 0);
	secmicappendbyte(pmicdata, 0);
	secmicappendbyte(pmicdata, 0);

	while (pmicdata->nBytesInM != 0)
		secmicappendbyte(pmicdata, 0);

	secmicputuint32(dst, pmicdata->L);
	secmicputuint32(dst + 4, pmicdata->R);

	secmicclear(pmicdata);
}
