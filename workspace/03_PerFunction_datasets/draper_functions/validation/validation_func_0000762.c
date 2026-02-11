CopyFrame(frame_t *frame1, int copy)
{

	frame_t *frame2;

	if((copy==0) && (frame1->frflags & FRFLAG_COPIED))
	{

		return(frame1);
	}

	frame2 = AllocFrame();
	if(frame2 != NULL)
	{
		memcpy(frame2,frame1,sizeof(frame_t));
		frame2->length = 0;
		frame2->frflags |= FRFLAG_COPIED;
	}
	return(frame2);
}
