find_i (const ACE_TCHAR name[],
                                size_t &slot,
                                const ACE_Service_Type **srp,
                                bool ignore_suspended) const
{
  ACE_TRACE ("ACE_Service_Repository::find_i");
  size_t i = 0;
  array_type::const_iterator element = this->service_array_.end ();

  for (i = 0; i < this->service_array_.size(); i++)
    {
      array_type::const_iterator iter = this->service_array_.find (i);
      if (iter != this->service_array_.end ()
          && (*iter).second != 0
          && ACE_OS::strcmp (name, (*iter).second->name ()) == 0)
      {
        element = iter;
        break;
      }
    }

  if (element != this->service_array_.end ())
    {
      slot = i;
      if ((*element).second->fini_called ())
        {
          if (srp != 0)
            *srp = 0;
          return -1;
        }

      if (srp != 0)
        *srp = (*element).second;

      if (ignore_suspended
          && (*element).second->active () == 0)
        return -2;

      return 0;
    }

  return -1;
}
