DXIsElementValid(InvalidComponentHandle handle, int index)
{
    if (handle->sense == IC_MARKS_INDICATE_INVALID)
	return ! IsElementMarked(handle, index);
    else
	return IsElementMarked(handle, index);
}
