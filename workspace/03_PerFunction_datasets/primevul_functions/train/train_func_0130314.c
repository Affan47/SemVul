proto_reg_handoff_multipart(void)
{
    dissector_handle_t multipart_handle;


    media_handle = find_dissector_add_dependency("media", proto_multipart);
    gssapi_handle = find_dissector_add_dependency("gssapi", proto_multipart);


    media_type_dissector_table = find_dissector_table("media_type");


    multipart_handle = create_dissector_handle(
            dissect_multipart, proto_multipart);

    dissector_add_string("media_type",
            "multipart/mixed", multipart_handle);
    dissector_add_string("media_type",
            "multipart/related", multipart_handle);
    dissector_add_string("media_type",
            "multipart/alternative", multipart_handle);
    dissector_add_string("media_type",
            "multipart/form-data", multipart_handle);
    dissector_add_string("media_type",
            "multipart/report", multipart_handle);
    dissector_add_string("media_type",
            "multipart/signed", multipart_handle);
    dissector_add_string("media_type",
            "multipart/encrypted", multipart_handle);


    dissector_add_string("media_type",
            "multipart/", multipart_handle);
}
