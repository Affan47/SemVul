matches_filtered_tree(const authz_user_rules_t *authz,
                      const char *repos_name,
                      const char *user)
{

  if (user)
    {
      if (authz->user == NULL || strcmp(user, authz->user))
        return FALSE;
    }
  else if (authz->user != NULL)
    return FALSE;


  return strcmp(repos_name, authz->repository) == 0;
}
