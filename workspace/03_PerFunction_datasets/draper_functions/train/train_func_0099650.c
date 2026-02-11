toggle_firm_link(int linkId, int toggleFlag, char remoteAction, int setBoth)
{
	if( !remoteAction && remote.is_enable() )
	{

		short *shortPtr = (short *)remote.new_send_queue_msg(MSG_FIRM_TOGGLE_LINK_FIRM, 3*sizeof(short));
		shortPtr[0] = firm_recno;
		shortPtr[1] = linkId;
		shortPtr[2] = toggleFlag;
		return;
	}

	int linkedNationRecno = firm_array[linked_firm_array[linkId-1]]->nation_recno;

	int sameNation = linkedNationRecno == nation_recno ||
						  linkedNationRecno == 0 ||
                    nation_recno == 0;

	if( toggleFlag )
   {
		if( (sameNation && setBoth==0) || setBoth==1 )
			linked_firm_enable_array[linkId-1] = LINK_EE;
		else
			linked_firm_enable_array[linkId-1] |= LINK_ED;
	}
	else
	{
		if( (sameNation && setBoth==0) || setBoth==1 )
			linked_firm_enable_array[linkId-1] = LINK_DD;
      else
         linked_firm_enable_array[linkId-1] &= ~LINK_ED;
   }


	if(firm_id == FIRM_HARBOR)
	{
		FirmHarbor *harborPtr = (FirmHarbor*) this;
		harborPtr->link_checked = 0;
	}


	Firm* firmPtr = firm_array[ linked_firm_array[linkId-1] ];


	if(firmPtr->firm_id==FIRM_HARBOR)
	{
		FirmHarbor *harborPtr = (FirmHarbor*) firmPtr;
		harborPtr->link_checked = 0;
	}

   int   i;

   for( i=0 ; i<firmPtr->linked_firm_count ; i++ )
   {
      if( firmPtr->linked_firm_array[i] == firm_recno )
      {
			if( toggleFlag )
			{
				if( (sameNation && setBoth==0) || setBoth==1 )
					firmPtr->linked_firm_enable_array[i]  = LINK_EE;
				else
					firmPtr->linked_firm_enable_array[i] |= LINK_DE;
			}
			else
			{
				if( (sameNation && setBoth==0) || setBoth==1 )
					firmPtr->linked_firm_enable_array[i]  = LINK_DD;
            else
               firmPtr->linked_firm_enable_array[i] &= ~LINK_DE;
         }

			break;
      }
   }
}
