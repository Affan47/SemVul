currentLn(Buffer *buf)
{
    if (buf->currentLine)

	return buf->currentLine->linenumber + 1;
    else
	return 1;
}
