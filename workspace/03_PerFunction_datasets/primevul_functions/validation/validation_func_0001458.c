static void exif_thumbnail_extract(image_info_type *ImageInfo,
                                   char *offset, size_t length) {
  if (ImageInfo->Thumbnail.data) {
    raise_warning("Multiple possible thumbnails");
    return;
  }
  if (!ImageInfo->read_thumbnail) {
    return;
  }


  if (ImageInfo->Thumbnail.size >= 65536 ||
      ImageInfo->Thumbnail.size <= 0 ||
      ImageInfo->Thumbnail.offset <= 0) {
    raise_warning("Illegal thumbnail size/offset");
    return;
  }

  if ((ImageInfo->Thumbnail.offset + ImageInfo->Thumbnail.size) > length) {
    raise_warning("Thumbnail goes IFD boundary or end of file reached");
    return;
  }
  PHP_STRNDUP(ImageInfo->Thumbnail.data, offset + ImageInfo->Thumbnail.offset,
              ImageInfo->Thumbnail.size);
  exif_thumbnail_build(ImageInfo);
}
