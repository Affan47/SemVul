P_ArchiveWorld (void)
{
    int			i;
    int			j;
    sector_t*		sec;
    line_t*		li;
    side_t*		si;


    for (i=0, sec = sectors ; i<numsectors ; i++,sec++)
    {
	saveg_write16(sec->floorheight >> FRACBITS);
	saveg_write16(sec->ceilingheight >> FRACBITS);
	saveg_write16(sec->floorpic);
	saveg_write16(sec->ceilingpic);
	saveg_write16(sec->lightlevel);
	saveg_write16(sec->special);
	saveg_write16(sec->tag);
    }


    for (i=0, li = lines ; i<numlines ; i++,li++)
    {
	saveg_write16(li->flags);
	saveg_write16(li->special);
	saveg_write16(li->tag);
	for (j=0 ; j<2 ; j++)
	{
	    if (li->sidenum[j] == -1)
		continue;

	    si = &sides[li->sidenum[j]];

	    saveg_write16(si->textureoffset >> FRACBITS);
	    saveg_write16(si->rowoffset >> FRACBITS);
	    saveg_write16(si->toptexture);
	    saveg_write16(si->bottomtexture);
	    saveg_write16(si->midtexture);
	}
    }
}
