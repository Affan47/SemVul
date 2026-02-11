_cdk_keydb_check_userid (cdk_keydb_hd_t hd, u32 * keyid, const char *id)
{
  cdk_kbnode_t knode = NULL, unode = NULL;
  cdk_error_t rc;
  int check;
  cdk_keydb_search_t st;

  if (!hd)
    {
      gnutls_assert ();
      return CDK_Inv_Value;
    }

  rc = cdk_keydb_search_start (&st, hd, CDK_DBSEARCH_KEYID, keyid);
  if (rc)
    {
      gnutls_assert ();
      return rc;
    }
  rc = cdk_keydb_search (st, hd, &knode);
  cdk_keydb_search_release (st);

  if (rc)
    {
      gnutls_assert ();
      return rc;
    }

  rc = cdk_keydb_search_start (&st, hd, CDK_DBSEARCH_EXACT, (char *) id);
  if (!rc)
    {
      rc = cdk_keydb_search (st, hd, &unode);
      cdk_keydb_search_release (st);
    }
  if (rc)
    {
      cdk_kbnode_release (knode);
      gnutls_assert ();
      return rc;
    }

  check = 0;
  cdk_keydb_search_start (&st, hd, CDK_DBSEARCH_KEYID, keyid);
  if (unode && find_by_keyid (unode, st))
    check++;
  cdk_keydb_search_release (st);
  cdk_kbnode_release (unode);

  cdk_keydb_search_start (&st, hd, CDK_DBSEARCH_EXACT, (char *) id);
  if (knode && find_by_pattern (knode, st))
    check++;
  cdk_keydb_search_release (st);
  cdk_kbnode_release (knode);

  return check == 2 ? 0 : CDK_Inv_Value;
}
