BitPack(unsigned char *Dest, int CurrentBit, unsigned char *Source, int Bits)
{
	int i;

	for (i=0; i<Bits; i++)
		if (gn_ringtone_get_bit(Source, i))
			gn_ringtone_set_bit(Dest, CurrentBit+i);
		else
			gn_ringtone_clear_bit(Dest, CurrentBit+i);

	return CurrentBit+Bits;
}
