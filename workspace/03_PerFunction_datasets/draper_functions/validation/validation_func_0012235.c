sisfb_post_xgi_delay(struct sis_video_info *ivideo, int delay)
{
	unsigned int i;
	u8 reg;

	for(i = 0; i <= (delay * 10 * 36); i++) {
		reg = SiS_GetReg(SISSR, 0x05);
		reg++;
	}
}
