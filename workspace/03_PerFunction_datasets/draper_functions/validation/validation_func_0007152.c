rbd_img_request_op_type(struct rbd_img_request *img_request)
{
	if (img_request_write_test(img_request))
		return OBJ_OP_WRITE;
	else if (img_request_discard_test(img_request))
		return OBJ_OP_DISCARD;
	else
		return OBJ_OP_READ;
}
