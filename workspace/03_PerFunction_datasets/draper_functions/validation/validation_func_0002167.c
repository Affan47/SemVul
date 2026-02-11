sendString(
	FLMUINT			uiTag,
	FLMUNICODE *	puzString)
{
	RCODE				rc = FERR_OK;


	switch( uiTag)
	{
		case WIRE_VALUE_FILE_NAME:
		case WIRE_VALUE_FILE_PATH:
		case WIRE_VALUE_FILE_PATH_2:
		case WIRE_VALUE_FILE_PATH_3:
		case WIRE_VALUE_DICT_FILE_PATH:
		case WIRE_VALUE_ITEM_NAME:
		case WIRE_VALUE_DICT_BUFFER:
		{
			uiTag |= WIRE_VALUE_TYPE_UTF <<
				WIRE_VALUE_TYPE_START_BIT;

			if( RC_BAD( rc = m_pDOStream->writeUShort( (FLMUINT16)uiTag)))
			{
				goto Exit;
			}

			if( RC_BAD( rc = m_pDOStream->writeUTF( puzString)))
			{
				goto Exit;
			}
			break;
		}

		default:
		{
#ifdef FLM_DEBUG
			flmAssert( 0);
#else
			rc = RC_SET( FERR_NOT_IMPLEMENTED);
			goto Exit;
#endif
		}
	}

Exit:

	return( rc);
}
