create_user_authz(authz_full_t *authz,
                  const char *repository,
                  const char *user,
                  apr_pool_t *result_pool,
                  apr_pool_t *scratch_pool)
{
  int i;
  node_t *root = create_node(NULL, result_pool);
  construction_context_t *ctx = create_construction_context(scratch_pool);


  apr_pool_t *subpool = svn_pool_create(scratch_pool);


  apr_array_header_t *acls = apr_array_make(subpool, authz->acls->nelts,
                                            sizeof(authz_acl_t *));
  for (i = 0; i < authz->acls->nelts; ++i)
    {
      const authz_acl_t *acl = &APR_ARRAY_IDX(authz->acls, i, authz_acl_t);
      if (svn_authz__acl_applies_to_repo(acl, repository))
        {


          if (acls->nelts)
            {
              const authz_acl_t *prev_acl
                = APR_ARRAY_IDX(acls, acls->nelts - 1, const authz_acl_t *);
              if (svn_authz__compare_paths(&prev_acl->rule, &acl->rule) == 0)
                {
                  svn_boolean_t global_acl_applies;
                  svn_boolean_t repos_acl_applies;


                  SVN_ERR_ASSERT_NO_RETURN(!strcmp(prev_acl->rule.repos,
                                                   AUTHZ_ANY_REPOSITORY));

                  SVN_ERR_ASSERT_NO_RETURN(strcmp(acl->rule.repos,
                                                  AUTHZ_ANY_REPOSITORY));

                  global_acl_applies =
                    svn_authz__get_acl_access(NULL, prev_acl, user, repository);
                  repos_acl_applies =
                    svn_authz__get_acl_access(NULL, acl, user, repository);


                  if (!global_acl_applies || repos_acl_applies)
                    {
                      apr_array_pop(acls);
                      APR_ARRAY_PUSH(acls, const authz_acl_t *) = acl;
                    }
                }
              else
                APR_ARRAY_PUSH(acls, const authz_acl_t *) = acl;
            }
          else
            APR_ARRAY_PUSH(acls, const authz_acl_t *) = acl;
        }
    }


  for (i = 0; i < acls->nelts; ++i)
    process_acl(ctx, APR_ARRAY_IDX(acls, i, const authz_acl_t *),
                root, repository, user, result_pool, subpool);


  if (!has_local_rule(&root->rights))
    {
      root->rights.access.sequence_number = 0;
      root->rights.access.rights = authz_access_none;
    }


  svn_pool_clear(subpool);
  trim_tree(root, NO_SEQUENCE_NUMBER, subpool);


  svn_pool_clear(subpool);
  finalize_tree(root, &root->rights, subpool);


  svn_pool_destroy(subpool);
  return root;
}
