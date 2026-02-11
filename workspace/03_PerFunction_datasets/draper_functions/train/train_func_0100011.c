remove (void *object)
{
  ACE_Cleanup_Info_Node *node = 0;
  for (ACE_Cleanup_Info_Node *iter = registered_objects_.head ();
       iter != 0;
       iter = iter->next ())
    {
      if (iter->object () == object)
        {
          node = iter;
          break;
        }
    }

  if (node)
    {
      registered_objects_.remove (node);
      delete node;
      return true;
    }

  return false;
}
