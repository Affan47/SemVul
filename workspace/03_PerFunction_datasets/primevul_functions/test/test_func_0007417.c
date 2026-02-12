static void mod_wstunnel_merge_config_cpv(plugin_config * const pconf, const config_plugin_value_t * const cpv) {
    switch (cpv->k_id) {
      case 0:
        if (cpv->vtype == T_CONFIG_LOCAL) {
            gw_plugin_config * const gw = cpv->v.v;
            pconf->gw.exts      = gw->exts;
            pconf->gw.exts_auth = gw->exts_auth;
            pconf->gw.exts_resp = gw->exts_resp;
        }
        break;
      case 1:

            pconf->gw.balance = (int)cpv->v.u;
        break;
      case 2:
        pconf->gw.debug = (int)cpv->v.u;
        break;
      case 3:
        pconf->gw.ext_mapping = cpv->v.a;
        break;
      case 4:
        pconf->frame_type = cpv->v.u;
        break;
      case 5:
        pconf->origins = cpv->v.a;
        break;
      case 6:
        pconf->ping_interval = cpv->v.shrt;
        break;
      default:
        return;
    }
}
