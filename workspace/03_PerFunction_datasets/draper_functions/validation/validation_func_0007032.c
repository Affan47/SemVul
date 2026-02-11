tableInqNamePtr(int tableID)
{
  char *tablename = NULL;

  if ( CDI_Debug )
    Message("tableID = %d", tableID);

  if ( ! ParTableInit ) parTableInit();

  if ( tableID >= 0 && tableID < parTableSize )
    if ( parTable[tableID].name )
      tablename = parTable[tableID].name;

  return (tablename);
}
