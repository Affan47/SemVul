void RGWGetBucketPolicyStatus_ObjStore_S3::send_response()
{
  if (op_ret) {
    set_req_state_err(s, op_ret);
  }
  dump_errno(s);
  end_header(s, this, "application/xml");
  dump_start(s);

  s->formatter->open_object_section_in_ns("PolicyStatus", XMLNS_AWS_S3);


  s->formatter->dump_bool("IsPublic", isPublic);
  s->formatter->close_section();
  rgw_flush_formatter_and_reset(s, s->formatter);

}
