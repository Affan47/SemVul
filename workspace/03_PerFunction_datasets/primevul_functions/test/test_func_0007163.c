get_user_rules(svn_authz_t *authz,
               const char *repos_name,
               const char *user)
{
  apr_pool_t *pool;


  if (authz->filtered)
    {

      if (matches_filtered_tree(authz->filtered, repos_name, user))
        return authz->filtered;


      svn_pool_destroy(authz->filtered->pool);
      authz->filtered = NULL;
    }


  pool = svn_pool_create(authz->pool);


  authz->filtered = apr_palloc(pool, sizeof(*authz->filtered));
  authz->filtered->pool = pool;
  authz->filtered->repository = apr_pstrdup(pool, repos_name);
  authz->filtered->user = user ? apr_pstrdup(pool, user) : NULL;
  authz->filtered->lookup_state = create_lookup_state(pool);
  authz->filtered->root = NULL;

  svn_authz__get_global_rights(&authz->filtered->global_rights,
                               authz->full, user, repos_name);

  return authz->filtered;
}
