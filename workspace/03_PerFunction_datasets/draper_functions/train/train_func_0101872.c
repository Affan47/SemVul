sierra_next_section()
{
    int i,j;

    for (i=0; i<16; i++)
        track[i].on=0;

    midiprintf("\n\nnext adv sierra section:\n");

    pos=sierra_pos;
    i=0;j=0;
    while (i!=0xff)
       {
       getnext(1);
       curtrack=j; j++;
       track[curtrack].on=1;
	   track[curtrack].spos = getnext(1);
	   track[curtrack].spos += (getnext(1) << 8) + 4;

       track[curtrack].tend=flen;
       track[curtrack].iwait=0;
       track[curtrack].pv=0;
       midiprintf ("track %d starts at %lx\n",curtrack,track[curtrack].spos);

       getnext(2);
       i=getnext(1);
       }
    getnext(2);
    deltas=0x20;
    sierra_pos=pos;


    fwait=0;
    doing=1;
}
