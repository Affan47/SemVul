SiS_SetCRT1Offset(struct SiS_Private *SiS_Pr, unsigned short ModeNo,
		  unsigned short ModeIdIndex, unsigned short rrti)
{
	unsigned short du = SiS_GetOffset(SiS_Pr, ModeNo, ModeIdIndex, rrti);
	unsigned short infoflag = SiS_Pr->SiS_RefIndex[rrti].Ext_InfoFlag;
	unsigned short temp;

	temp = (du >> 8) & 0x0f;
	SiS_SetRegANDOR(SiS_Pr, SiS_Pr->SiS_P3c4, 0x0E, 0xF0, temp);

	SiS_SetReg(SiS_Pr, SiS_Pr->SiS_P3d4, 0x13, (du & 0xFF));

	if (infoflag & InterlaceMode)
		du >>= 1;

	du <<= 5;
	temp = (du >> 8) & 0xff;
	if (du & 0xff)
		temp++;
	temp++;
	SiS_SetReg(SiS_Pr, SiS_Pr->SiS_P3c4, 0x10, temp);
}
