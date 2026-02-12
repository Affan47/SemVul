_dbus_error_from_gai (int gai_res,
                      int saved_errno)
{
  switch (gai_res)
    {
#ifdef EAI_FAMILY
      case EAI_FAMILY:

        return DBUS_ERROR_NOT_SUPPORTED;
#endif

#ifdef EAI_SOCKTYPE
      case EAI_SOCKTYPE:

        return DBUS_ERROR_NOT_SUPPORTED;
#endif

#ifdef EAI_MEMORY
      case EAI_MEMORY:

        return DBUS_ERROR_NO_MEMORY;
#endif

#ifdef EAI_SYSTEM
      case EAI_SYSTEM:

        return _dbus_error_from_errno (saved_errno);
#endif

      case 0:

        return DBUS_ERROR_FAILED;


      default:
        return DBUS_ERROR_FAILED;
    }
}
