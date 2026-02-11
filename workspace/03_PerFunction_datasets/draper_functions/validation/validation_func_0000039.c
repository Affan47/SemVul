has_function_state (struct cgraph_node *node)
{
  if (!funct_state_vec.exists ()
      || funct_state_vec.length () <= (unsigned int)node->uid)
    return false;
  return funct_state_vec[node->uid] != NULL;
}
