Populate_Select_Cache( ITD_Struct *Server,
				  ISC_Struct *ISC,
				  char *MailboxName,
				  char *ClientCommand,
				  unsigned int Length )
{
    char *fn = "Populate_Select_Cache()";
    int rc;
    int BytesLeftInBuffer = SELECT_BUF_SIZE;
    char *BufPtr;
    char *CP;
    char *EOS;

    rc = IMAP_Write( Server->conn, ClientCommand, Length );

    if ( rc == -1 )
    {
	syslog( LOG_ERR, "%s: Unable to send SELECT command to imap server so can't populate cache.", fn );
	return( -1 );
    }

    BufPtr = ISC->SelectString;

    for( ;; )
    {
	if ( Server->LiteralBytesRemaining )
	{
	    syslog( LOG_ERR, "%s: Server response to SELECT command contains unexpected literal data on sd [%d].",
	        fn, Server->conn );


	    while ( Server->LiteralBytesRemaining )
	    {
		IMAP_Literal_Read( Server );
	    }

	    return( -1 );
	}

	rc = IMAP_Line_Read( Server );

	if ( ( rc == -1 ) || ( rc == 0 ) )
	{
	    syslog( LOG_WARNING, "%s: Unable to read SELECT response from imap server so can't populate cache.", fn );
	    return( -1 );
	}


	if ( Server->ReadBuf[0] != '*' )
	    break;

	if ( rc >= BytesLeftInBuffer )
	{
	    syslog( LOG_WARNING, "%s: Size of SELECT response from server exceeds max cache size of %d bytes.  Unable to cache this response.", fn, SELECT_BUF_SIZE );
	    return( -1 );
	}

	memcpy( (void *)BufPtr, (const void *)Server->ReadBuf, rc );
	BytesLeftInBuffer -= rc;
	BufPtr += rc;
    }


    *BufPtr = '\0';


    CP = memchr( (const void *)Server->ReadBuf, ' ', rc );
    if ( ! CP )
    {
	syslog( LOG_ERR, "%s: Invalid response to SELECT command.  Contains no tokens.", fn );
	return( -1 );
    }
    CP++;

    EOS = memchr( (const void *)Server->ReadBuf, '\r', rc );
    if ( ! EOS )
    {
	syslog( LOG_ERR, "%s: Invalid response to SELECT command.  Not CRLF terminated.", fn );
	return( -1 );
    }

    *EOS = '\0';
    snprintf( (char *)ISC->SelectStatus, SELECT_STATUS_BUF_SIZE - 1, "%s\r\n",
	      CP );
    *EOS = '\r';


    ISC->ISCTime = time( 0 );

    strncpy( (char *)ISC->MailboxName, (const char *)MailboxName, MAXMAILBOXNAME - 1 );
    ISC->MailboxName[ MAXMAILBOXNAME - 1 ] = '\0';

    return( 0 );

}
