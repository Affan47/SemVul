DECtoASCII(unsigned ch)
{
    if (xtermIsDecGraphic(ch)) {
	ch = CharOf("###########+++++##-##++++|######"[ch]);

    }
    return ch;
}
