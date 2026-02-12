svn_repos_authz_check_access(svn_authz_t *authz, const char *repos_name,
                             const char *path, const char *user,
                             svn_repos_authz_access_t required_access,
                             svn_boolean_t *access_granted,
                             apr_pool_t *pool)
{
  const authz_access_t required =
    ((required_access & svn_authz_read ? authz_access_read_flag : 0)
     | (required_access & svn_authz_write ? authz_access_write_flag : 0));


  authz_user_rules_t *rules = get_user_rules(
      authz,
      (repos_name ? repos_name : AUTHZ_ANY_REPOSITORY),
      user);


  if ((rules->global_rights.min_access & required) == required)
    {
      *access_granted = TRUE;
      return SVN_NO_ERROR;
    }

  if ((rules->global_rights.max_access & required) != required)
    {
      *access_granted = FALSE;
      return SVN_NO_ERROR;
    }


  if (!path)
    {
      *access_granted =
        ((rules->global_rights.max_access & required) == required);
      return SVN_NO_ERROR;
    }


  if (!rules->root)
    SVN_ERR(filter_tree(authz, pool));


  path = init_lockup_state(authz->filtered->lookup_state,
                           authz->filtered->root, path);


  SVN_ERR_ASSERT(path[0] == '/');


  *access_granted = lookup(rules->lookup_state, path, required,
                           !!(required_access & svn_authz_recursive), pool);

  return SVN_NO_ERROR;
}
