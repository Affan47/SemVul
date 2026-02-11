_dbus_user_database_lookup (DBusUserDatabase *db,
                            dbus_uid_t        uid,
                            const DBusString *username,
                            DBusError        *error)
{
  DBusUserInfo *info;

  _DBUS_ASSERT_ERROR_IS_CLEAR (error);
  _dbus_assert (uid != DBUS_UID_UNSET || username != NULL);


  if (uid == DBUS_UID_UNSET)
    {
      unsigned long n;

      if (_dbus_is_a_number (username, &n))
        uid = n;
    }

#ifdef DBUS_ENABLE_USERDB_CACHE
  if (uid != DBUS_UID_UNSET)
    info = _dbus_hash_table_lookup_uintptr (db->users, uid);
  else
    info = _dbus_hash_table_lookup_string (db->users_by_name, _dbus_string_get_const_data (username));

  if (info)
    {
      _dbus_verbose ("Using cache for UID "DBUS_UID_FORMAT" information\n",
                     info->uid);
      return info;
    }
  else
#else
  if (1)
#endif
    {
      if (uid != DBUS_UID_UNSET)
	_dbus_verbose ("No cache for UID "DBUS_UID_FORMAT"\n",
		       uid);
      else
	_dbus_verbose ("No cache for user \"%s\"\n",
		       _dbus_string_get_const_data (username));

      info = dbus_new0 (DBusUserInfo, 1);
      if (info == NULL)
        {
          dbus_set_error (error, DBUS_ERROR_NO_MEMORY, NULL);
          return NULL;
        }

      if (uid != DBUS_UID_UNSET)
        {
          if (!_dbus_user_info_fill_uid (info, uid, error))
            {
              _DBUS_ASSERT_ERROR_IS_SET (error);
              _dbus_user_info_free_allocated (info);
              return NULL;
            }
        }
      else
        {
          if (!_dbus_user_info_fill (info, username, error))
            {
              _DBUS_ASSERT_ERROR_IS_SET (error);
              _dbus_user_info_free_allocated (info);
              return NULL;
            }
        }


      uid = DBUS_UID_UNSET;
      username = NULL;


      if (!_dbus_hash_table_insert_uintptr (db->users, info->uid, info))
        {
          dbus_set_error (error, DBUS_ERROR_NO_MEMORY, NULL);
          _dbus_user_info_free_allocated (info);
          return NULL;
        }

      if (!_dbus_hash_table_insert_string (db->users_by_name,
                                           info->username,
                                           info))
        {
          _dbus_hash_table_remove_uintptr (db->users, info->uid);
          dbus_set_error (error, DBUS_ERROR_NO_MEMORY, NULL);
          return NULL;
        }

      return info;
    }
}
