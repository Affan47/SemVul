zlib_wrapper (OOP oop, int flush, int inSize, int (*func) (z_stream *, int))
{
  zlib_stream zs = (zlib_stream) OOP_TO_OBJ (oop);
  z_stream *zlib_obj = vmProxy->OOPToCObject (zs->zlibObject);
  OOP inBytesOOP = zs->inBytes;
  OOP outBytesOOP = zs->outBytes;
  char *inBytes = &STRING_OOP_AT (OOP_TO_OBJ (inBytesOOP), 1);
  char *outBytes = &STRING_OOP_AT (OOP_TO_OBJ (outBytesOOP), 1);
  size_t outSize = vmProxy->OOPSize (outBytesOOP);
  int ret;

  if (!zlib_obj)
    return -1;


  if (zlib_obj->opaque)
    zlib_obj->next_in = inBytes + (ptrdiff_t) zlib_obj->opaque;
  else
    {
      zlib_obj->next_in = inBytes;
      zlib_obj->avail_in = inSize;
    }


  zlib_obj->next_out = outBytes;
  zlib_obj->avail_out = outSize;
  ret = func (zlib_obj, flush);
  if (ret == Z_BUF_ERROR)
    {
      zlib_obj->msg = NULL;
      ret = Z_OK;
    }


  if (zlib_obj->avail_in == 0)
    {
      zs->inBytes = vmProxy->nilOOP;
      zlib_obj->opaque = NULL;
    }
  else
    zlib_obj->opaque = (PTR) ((char *) zlib_obj->next_in - (char *) inBytes);


  if (ret < 0)
    return -1;
  else if (flush == Z_FINISH && inSize == 0 && outSize == zlib_obj->avail_out)
    return -1;
  else
    return outSize - zlib_obj->avail_out;
}
