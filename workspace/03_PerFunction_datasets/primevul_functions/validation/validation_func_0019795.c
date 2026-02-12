void RGWCopyObj_ObjStore_SWIFT::dump_copy_info()
{

  dump_header(s, "X-Copied-From", url_encode(src_bucket.name) +
              "/" + url_encode(src_object.name));


  dump_header(s, "X-Copied-From-Account", url_encode(s->user->user_id.id));


  dump_time_header(s, "X-Copied-From-Last-Modified", src_mtime);
}
