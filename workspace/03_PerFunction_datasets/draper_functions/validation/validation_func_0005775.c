vorbis_stream_destroy(vorbis_stream_t *vorbis) {
  ogg_page_destroy(&vorbis->page);
  vorbis->segment = 0;

  int i;
  for (i = 0; i < VORBIS_MAX_HDR_PAGES; i++)
    ogg_page_destroy(vorbis->hdr_pages + i);

  buf_free(&vorbis->id_hdr);
  buf_free(&vorbis->comment_hdr);
  buf_free(&vorbis->setup_hdr);
}
