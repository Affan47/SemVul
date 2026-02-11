open (size_t size)
{
  ACE_TRACE ("ACE_Service_Repository::open");


  array_type local_array (size);
  this->service_array_.swap (local_array);

  return 0;
}
