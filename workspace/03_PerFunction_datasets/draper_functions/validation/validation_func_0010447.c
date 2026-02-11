release()
{
  if(!released)
    {
      if(cache.group_level == 0)
	std::cerr << "W: Unbalanced action groups, expect badness" << std::endl;
      else
	{
	  --cache.group_level;

	  if(cache.group_level == 0)
	    cache.MarkAndSweep();
	}

      released = true;
    }
}
