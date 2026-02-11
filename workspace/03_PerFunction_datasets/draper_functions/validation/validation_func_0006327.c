camlidl_texpr1_ap_texpr1_to_expr(value _v_texpr)
{
CAMLparam1(_v_texpr);
CAMLlocal1(_v_res);
ap_environment_t* env;
ap_texpr1_t texpr1;

struct camlidl_ctx_struct _ctxs = { CAMLIDL_TRANSIENT, NULL };
camlidl_ctx _ctx = &_ctxs;

camlidl_ml2c_texpr1_struct_ap_texpr1_t(_v_texpr,&texpr1,_ctx);
_v_res = camlidl_texpr1_ap_texpr1_to_expr_c2ml(texpr1.env,texpr1.texpr0,_ctx);
camlidl_free(_ctx);

CAMLreturn(_v_res);
}
