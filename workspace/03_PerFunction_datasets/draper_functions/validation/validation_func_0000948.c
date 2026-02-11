get_tempo_info_from_track_1 ()
{


    static int chantype[] = {
	0, 0, 0, 0, 0, 0, 0, 0,
	2, 2, 2, 2, 1, 1, 2, 0
    };
    long lookfor;
    int c, c1, type;
    int sysexcontinue = 0;
    int running = 0;
    int status = 0;
    int needed;
    long varinum;
    int position;
    char *m;

    position = ftell(F_in);


    if (readmt("MTrk") == EOF)
	return (0);

    Mf_toberead = read32bit();
    Mf_currtime = 0;


    while (Mf_toberead > 0) {

	delta_time = readvarinum();
	Mf_currtime += delta_time;

	c = egetc();

	if (sysexcontinue && c != 0xf7)
	    mferror("didn't find expected continuation of a sysex");

	if ((c & 0x80) == 0) {
	    if (status == 0)
		mferror("unexpected running status");
	    running = 1;
	} else {
	    status = c;
	    running = 0;
	}

	needed = chantype[(status >> 4) & 0xf];

	if (needed) {


	    if (running)
		c1 = c;
	    else
		c1 = egetc();

	    continue;;
	}

	switch (c) {

	case 0xff:

	    type = egetc();
	    varinum = readvarinum();
	    lookfor = Mf_toberead - varinum;
	    msginit();

	    while (Mf_toberead > lookfor)
		msgadd(egetc());


            if (type == 0x51) {
             m = msg();
             mf_get_tempo_event(to32bit(0,m[0],m[1],m[2]));
             }
	    break;

	case 0xf0:

	    varinum = readvarinum();
	    lookfor = Mf_toberead - varinum;
	    msginit();
	    msgadd(0xf0);

	    while (Mf_toberead > lookfor)
		msgadd(c = egetc());

	    if (c == 0xf7 || Mf_nomerge == 0)

                break;
	    else
		sysexcontinue = 1;
	    break;

	case 0xf7:

	    varinum = readvarinum();
	    lookfor = Mf_toberead - varinum;

	    if (!sysexcontinue)
		msginit();

	    while (Mf_toberead > lookfor)
		msgadd(c = egetc());

	    if (!sysexcontinue) {
		if (Mf_arbitrary)
		    (*Mf_arbitrary) (msgleng(), msg());
	    } else if (c == 0xf7) {

		sysexcontinue = 0;
	    }
	    break;
	default:
	    badbyte(c);
	    break;
	}
    }
fseek(F_in,position,SEEK_SET);
return(0);
}
