fgwait_for_packet (qdaemon, freturncontrol, ctimeout, cretries)
     struct sdaemon *qdaemon;
     boolean freturncontrol;
     int ctimeout;
     int cretries;
{
  int ctimeouts;
  int cgarbage;
  int cshort;

  ctimeouts = 0;
  cgarbage = 0;
  cshort = 0;

  while (TRUE)
    {
      boolean fexit;
      size_t cneed;
      boolean ffound;
      size_t crec;

      if (! fgprocess_data (qdaemon, TRUE, freturncontrol, &fexit,
			    &cneed, &ffound))
	return FALSE;

      if (fexit)
	return TRUE;

      DEBUG_MESSAGE1 (DEBUG_PROTO,
		      "fgwait_for_packet: Need %lu bytes",
		      (unsigned long) cneed);

      if (ffound)
	{
	  ctimeouts = 0;
	  cgarbage = 0;
	}
      else
	{
	  if (cgarbage > cGgarbage_data)
	    {
	      ulog (LOG_ERROR, "Too much unrecognized data");
	      return FALSE;
	    }
	}

      if (! freceive_data (qdaemon->qconn, cneed, &crec, ctimeout, TRUE))
	return FALSE;

      cgarbage += crec;

      if (crec != 0)
	{


	  if (crec >= cneed)
	    cshort = 0;
	  else
	    {
	      ++cshort;
	      if (cshort > 1)
		{
		  iPrecstart = (iPrecstart + 1) % CRECBUFLEN;
		  cshort = 0;
		}
	    }
	}
      else
	{


	  ++ctimeouts;
	  if (ctimeouts > cretries)
	    {
	      if (cretries > 0)
		ulog (LOG_ERROR, "Timed out waiting for packet");
	      return FALSE;
	    }

	  if (INEXTSEQ (iGremote_ack) != iGsendseq)
	    {
	      int inext;
	      char *zsend;

	      inext = INEXTSEQ (iGremote_ack);

	      DEBUG_MESSAGE1 (DEBUG_PROTO | DEBUG_ABNORMAL,
			      "fgwait_for_packet: Resending packet %d",
			      inext);

	      ++cGresent_packets;
	      zsend = zgadjust_ack (inext);
	      if (! fsend_data (qdaemon->qconn, zsend,
				CFRAMELEN + CPACKLEN (zsend), TRUE))
		return FALSE;
	      iGretransmit_seq = inext;
	    }
	  else
	    {


	      if (iGlocal_ack != iGrecseq)
		{
		  if (! fgsend_acks (qdaemon))
		    return FALSE;
		}
	      if (! fgsend_control (qdaemon, RJ, iGrecseq))
		return FALSE;
	    }
	}
    }
}
