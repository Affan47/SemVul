static UINT rdpei_write_touch_frame(wStream* s, RDPINPUT_TOUCH_FRAME* frame)
{
	UINT32 index;
	int rectSize = 2;
	RDPINPUT_CONTACT_DATA* contact;
#ifdef WITH_DEBUG_RDPEI
	WLog_DBG(TAG, "contactCount: %" PRIu32 "", frame->contactCount);
	WLog_DBG(TAG, "frameOffset: 0x%016" PRIX64 "", frame->frameOffset);
#endif
	rdpei_write_2byte_unsigned(s,
	                           frame->contactCount);


	rdpei_write_8byte_unsigned(s, frame->frameOffset *
	                                  1000);

	if (!Stream_EnsureRemainingCapacity(s, (size_t)frame->contactCount * 64))
	{
		WLog_ERR(TAG, "Stream_EnsureRemainingCapacity failed!");
		return CHANNEL_RC_NO_MEMORY;
	}

	for (index = 0; index < frame->contactCount; index++)
	{
		contact = &frame->contacts[index];
		contact->fieldsPresent |= CONTACT_DATA_CONTACTRECT_PRESENT;
		contact->contactRectLeft = contact->x - rectSize;
		contact->contactRectTop = contact->y - rectSize;
		contact->contactRectRight = contact->x + rectSize;
		contact->contactRectBottom = contact->y + rectSize;
#ifdef WITH_DEBUG_RDPEI
		WLog_DBG(TAG, "contact[%" PRIu32 "].contactId: %" PRIu32 "", index, contact->contactId);
		WLog_DBG(TAG, "contact[%" PRIu32 "].fieldsPresent: %" PRIu32 "", index,
		         contact->fieldsPresent);
		WLog_DBG(TAG, "contact[%" PRIu32 "].x: %" PRId32 "", index, contact->x);
		WLog_DBG(TAG, "contact[%" PRIu32 "].y: %" PRId32 "", index, contact->y);
		WLog_DBG(TAG, "contact[%" PRIu32 "].contactFlags: 0x%08" PRIX32 "", index,
		         contact->contactFlags);
		rdpei_print_contact_flags(contact->contactFlags);
#endif
		Stream_Write_UINT8(s, contact->contactId);

		rdpei_write_2byte_unsigned(s, contact->fieldsPresent);
		rdpei_write_4byte_signed(s, contact->x);
		rdpei_write_4byte_signed(s, contact->y);

		rdpei_write_4byte_unsigned(s, contact->contactFlags);

		if (contact->fieldsPresent & CONTACT_DATA_CONTACTRECT_PRESENT)
		{

			rdpei_write_2byte_signed(s, contact->contactRectLeft);

			rdpei_write_2byte_signed(s, contact->contactRectTop);

			rdpei_write_2byte_signed(s, contact->contactRectRight);

			rdpei_write_2byte_signed(s, contact->contactRectBottom);
		}

		if (contact->fieldsPresent & CONTACT_DATA_ORIENTATION_PRESENT)
		{

			rdpei_write_4byte_unsigned(s, contact->orientation);
		}

		if (contact->fieldsPresent & CONTACT_DATA_PRESSURE_PRESENT)
		{

			rdpei_write_4byte_unsigned(s, contact->pressure);
		}
	}

	return CHANNEL_RC_OK;
}
