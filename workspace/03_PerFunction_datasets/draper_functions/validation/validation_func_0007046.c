open()
{

  if( opened ) close();

  load();

  return result == Storage::Ok;
}
