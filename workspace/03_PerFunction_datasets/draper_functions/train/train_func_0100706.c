mime_server_write_open(struct soap *soap, void *unused_handle, const char *id, const char *type, const char *description, enum soap_mime_encoding encoding)
{

  const char *file;
  struct mime_server_handle *handle = soap_malloc(soap, sizeof(struct mime_server_handle));
  if (!handle)
  { soap->error = SOAP_EOM;
    return NULL;
  }

  file = tempnam(TMPDIR, "data");

  handle->key = soap_strdup(soap, file);
  handle->fd = fopen(file, "wb");
  free((void*)file);
  if (!handle->fd)
  { soap->error = soap_sender_fault(soap, "Cannot save data to file", handle->key);
    soap->errnum = errno;
    return NULL;
  }
  fprintf(stderr, "Saving file %s type %s\n", handle->key, type?type:"");
  return (void*)handle;
}
