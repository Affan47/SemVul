int RGWHandler_REST_S3Website::init(RGWRados *store, req_state *s,
                                    rgw::io::BasicClient* cio)
{


  original_object_name = s->object.name;

  return RGWHandler_REST_S3::init(store, s, cio);
}
