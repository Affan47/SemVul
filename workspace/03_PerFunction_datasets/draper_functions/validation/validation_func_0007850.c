on_identity_refreshed (GoaIdentityManager *identity_manager,
                       GoaIdentity        *identity,
                       GoaIdentityService *self)
{
  GoaObject *object;
  const char *identifier;

  identifier = goa_identity_get_identifier (identity);
  object = find_object_with_principal (self, identifier, FALSE);

  if (object == NULL)
    add_temporary_account (self, identity);
  else
    ensure_account_credentials (self, object);
}
