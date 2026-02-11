EOLcode(u_long& w)
{
    if ((w & 0x00f00f) == 0) {
	EOLcheck(w, 0x00f0ff, 0x000080);
	EOLcheck(w, 0x00f87f, 0x000040);
	EOLcheck(w, 0x00fc3f, 0x000020);
	EOLcheck(w, 0x00fe1f, 0x000010);
    }
    if ((w & 0x00ff00) == 0) {
	EOLcheck(w, 0x00ff0f, 0x000008);
	EOLcheck(w, 0x80ff07, 0x000004);
	EOLcheck(w, 0xc0ff03, 0x000002);
	EOLcheck(w, 0xe0ff01, 0x000001);
    }
    if ((w & 0xf00f00) == 0) {
	EOLcheck(w, 0xf0ff00, 0x008000);
	EOLcheck(w, 0xf87f00, 0x004000);
	EOLcheck(w, 0xfc3f00, 0x002000);
	EOLcheck(w, 0xfe1f00, 0x001000);
    }
    return (false);
}
