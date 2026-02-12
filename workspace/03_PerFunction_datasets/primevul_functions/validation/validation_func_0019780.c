RGWOp* RGWSwiftWebsiteHandler::get_ws_listing_op()
{
  class RGWWebsiteListing : public RGWListBucket_ObjStore_SWIFT {
    const std::string prefix_override;

    int get_params() override {
      prefix = prefix_override;
      max = default_max;
      delimiter = "/";
      return 0;
    }

    void send_response() override {

      set_req_state_err(s, op_ret);
      dump_errno(s);
      dump_container_metadata(s, bucket, bucket_quota,
                              s->bucket_info.website_conf);
      end_header(s, this, "text/html");
      if (op_ret < 0) {
        return;
      }


      std::stringstream ss;
      RGWSwiftWebsiteListingFormatter htmler(ss, prefix);

      const auto& ws_conf = s->bucket_info.website_conf;
      htmler.generate_header(s->decoded_uri,
                             ws_conf.listing_css_doc);

      for (const auto& pair : common_prefixes) {
        std::string subdir_name = pair.first;
        if (! subdir_name.empty()) {


          subdir_name.pop_back();
        }

        htmler.dump_subdir(subdir_name);
      }

      for (const rgw_bucket_dir_entry& obj : objs) {
        if (! common_prefixes.count(obj.key.name + '/')) {
          htmler.dump_object(obj);
        }
      }

      htmler.generate_footer();
      dump_body(s, ss.str());
    }
  public:


    explicit RGWWebsiteListing(std::string prefix_override)
      : prefix_override(std::move(prefix_override)) {
    }
  };

  std::string prefix = std::move(s->object.name);
  s->object = rgw_obj_key();

  return new RGWWebsiteListing(std::move(prefix));
}
