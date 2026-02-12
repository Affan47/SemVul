static struct gfxinfo *php_handle_jp2(const req::ptr<File>& stream) {
  struct gfxinfo *result = nullptr;
  unsigned int box_length;
  unsigned int box_type;
  char jp2c_box_id[] = {(char)0x6a, (char)0x70, (char)0x32, (char)0x63};


  for (;;)
  {
    box_length = php_read4(stream);

    String str = stream->read(sizeof(box_type));
    if (str.length() != sizeof(box_type)) {

      break;
    }
    memcpy(&box_type, str.c_str(), sizeof(box_type));

    if (box_length == 1) {

      return nullptr;
    }

    if (!memcmp(&box_type, jp2c_box_id, 4))
    {

      stream->seek(3, SEEK_CUR);

      result = php_handle_jpc(stream);
      break;
    }


    if ((int)box_length <= 0) {
      break;
    }


    if (!stream->seek(box_length - 8, SEEK_CUR)) {
      break;
    }
  }

  if (result == nullptr) {
    raise_warning("JP2 file has no codestreams at root level");
  }

  return result;
}
