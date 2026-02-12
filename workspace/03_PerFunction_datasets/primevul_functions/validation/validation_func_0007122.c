int RGWGetObj_ObjStore_S3::get_params()
{


  skip_manifest = s->info.args.exists(RGW_SYS_PARAM_PREFIX "sync-manifest");


  if (s->system_request) {
    skip_decrypt = s->info.args.exists(RGW_SYS_PARAM_PREFIX "skip-decrypt");
  }

  return RGWGetObj_ObjStore::get_params();
}
