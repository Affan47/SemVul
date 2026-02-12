static struct gfxinfo *php_handle_jpc(const req::ptr<File>& file) {
  struct gfxinfo *result = nullptr;
  int highest_bit_depth, bit_depth;
  unsigned char first_marker_id;
  unsigned int i;


  first_marker_id = file->getc();


  if (first_marker_id != JPEG2000_MARKER_SIZ) {
    raise_warning("JPEG2000 codestream corrupt(Expected SIZ marker "
                    "not found after SOC)");
    return nullptr;
  }

  result = (struct gfxinfo *)IM_CALLOC(1, sizeof(struct gfxinfo));
  CHECK_ALLOC_R(result, sizeof (struct gfxinfo), nullptr);

  php_read2(file);
  php_read2(file);
  result->width = php_read4(file);
  result->height = php_read4(file);

#if MBO_0
  php_read4(file);
  php_read4(file);
  php_read4(file);
  php_read4(file);
  php_read4(file);
  php_read4(file);
#else
  if (!file->seek(24, SEEK_CUR)) {
    IM_FREE(result);
    return nullptr;
  }
#endif

  result->channels = php_read2(file);
  if (result->channels > 256) {
    IM_FREE(result);
    return nullptr;
  }


  highest_bit_depth = bit_depth = 0;
  for (i = 0; i < result->channels; i++) {
    bit_depth = file->getc();
    bit_depth++;
    if (bit_depth > highest_bit_depth) {
      highest_bit_depth = bit_depth;
    }

    file->getc();
    file->getc();
  }

  result->bits = highest_bit_depth;

  return result;
}
