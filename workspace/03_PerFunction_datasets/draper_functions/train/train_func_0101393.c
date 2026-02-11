GSgetBlock(GopherObj *gs, int bnum)
{
     if (gs->gplus == NULL || bnum < 0)
	  return(NULL);

     return(BLAgetEntry(gs->gplus->OtherBlocks, bnum));
}
