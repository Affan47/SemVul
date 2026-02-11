free_modules_db (struct gconv_module *node)
{
  if (node->left != NULL)
    free_modules_db (node->left);
  if (node->right != NULL)
    free_modules_db (node->right);
  do
    {
      struct gconv_module *act = node;
      node = node->same;
      if (act->module_name[0] == '/')
	free (act);
    }
  while (node != NULL);
}
