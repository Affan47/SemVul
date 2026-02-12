RGWOp* RGWHandler_REST_Obj_S3Website::get_obj_op(bool get_data)
{


  RGWGetObj_ObjStore_S3Website* op = new RGWGetObj_ObjStore_S3Website;
  op->set_get_data(get_data);
  return op;
}
