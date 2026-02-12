void RGWFormPost::get_owner_info(const req_state* const s,
                                   RGWUserInfo& owner_info) const
{


  const string& bucket_name = s->init_state.url_bucket;


  if (bucket_name.empty()) {
    throw -EPERM;
  }

  string bucket_tenant;
  if (!s->account_name.empty()) {
    RGWUserInfo uinfo;
    bool found = false;

    const rgw_user uid(s->account_name);
    if (uid.tenant.empty()) {
      const rgw_user tenanted_uid(uid.id, uid.id);

      if (rgw_get_user_info_by_uid(store, tenanted_uid, uinfo) >= 0) {

        bucket_tenant = uinfo.user_id.tenant;
        found = true;
      }
    }

    if (!found && rgw_get_user_info_by_uid(store, uid, uinfo) < 0) {
      throw -EPERM;
    } else {
      bucket_tenant = uinfo.user_id.tenant;
    }
  }


  RGWBucketInfo bucket_info;
  int ret = store->get_bucket_info(*s->sysobj_ctx,
                                   bucket_tenant, bucket_name,
                                   bucket_info, nullptr);
  if (ret < 0) {
    throw ret;
  }

  ldout(s->cct, 20) << "temp url user (bucket owner): " << bucket_info.owner
                 << dendl;

  if (rgw_get_user_info_by_uid(store, bucket_info.owner, owner_info) < 0) {
    throw -EPERM;
  }
}
