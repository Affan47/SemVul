static void ibwdt_ping(void)
{
	spin_lock(&ibwdt_lock);


	outb_p(wd_margin, WDT_START);

	spin_unlock(&ibwdt_lock);
}
