listing_list (int on)
{
  if (listing)
    {
      switch (on)
	{
	case 0:
	  if (listing_tail->edict == EDICT_LIST)
	    listing_tail->edict = EDICT_NONE;
	  else
	    listing_tail->edict = EDICT_NOLIST;
	  break;
	case 1:
	  if (listing_tail->edict == EDICT_NOLIST
	      || listing_tail->edict == EDICT_NOLIST_NEXT)
	    listing_tail->edict = EDICT_NONE;
	  else
	    listing_tail->edict = EDICT_LIST;
	  break;
	case 2:
	  listing_tail->edict = EDICT_NOLIST_NEXT;
	  break;
	default:
	  abort ();
	}
    }
}
