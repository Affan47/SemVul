camlidl_abstract0_ap_abstract0_bound_dimension(
	value _v_man,
	value _v_a,
	value _v_v)
{
  ap_manager_ptr man;
  ap_abstract0_ptr a;
  ap_dim_t v;
  struct ap_interval_t *_res;
  value _vres;

  struct camlidl_ctx_struct _ctxs = { CAMLIDL_TRANSIENT, NULL };
  camlidl_ctx _ctx = &_ctxs;
  camlidl_ml2c_manager_ap_manager_ptr(_v_man, &man, _ctx);
  camlidl_ml2c_abstract0_ap_abstract0_ptr(_v_a, &a, _ctx);
  camlidl_ml2c_dim_ap_dim_t(_v_v, &v, _ctx);
  _res = ap_abstract0_bound_dimension(man, a, v);
  _vres = camlidl_c2ml_interval_struct_ap_interval_t(&*_res, _ctx);
  camlidl_free(_ctx);

ap_interval_free(_res); if (man->result.exn!=AP_EXC_NONE) camlidl_apron_manager_check_exception(man,_ctx);

  return _vres;
}
