GF_Err gf_bifs_dec_field(GF_BifsDecoder * codec, GF_BitStream *bs, GF_Node *node, GF_FieldInfo *field, Bool is_mem_com)
{
	GF_Err e;
	u8 flag;


	assert(node);


	if (gf_sg_vrml_is_sf_field(field->fieldType)) {
		e = gf_bifs_dec_sf_field(codec, bs, node, field, is_mem_com);
		if (e) return e;
	} else {

		if (field->eventType == GF_SG_EVENT_IN) {
			if (field->fieldType == GF_SG_VRML_MFNODE) {
				gf_node_unregister_children(node, * (GF_ChildNodeItem **)field->far_ptr);
				* (GF_ChildNodeItem **)field->far_ptr = NULL;
			} else {

				e = gf_sg_vrml_mf_reset(field->far_ptr, field->fieldType);
				if (e) return e;
			}
		}


		if (codec->info->config.UsePredictiveMFField) {
			flag = gf_bs_read_int(bs, 1);
			if (flag) {
#ifdef GPAC_ENABLE_BIFS_PMF
				return gf_bifs_dec_pred_mf_field(codec, bs, node, field);
#else
				GF_LOG(GF_LOG_ERROR, GF_LOG_CODING, ("[BIFS] Stream uses Predictive Field Coding, disabled in this build!\n"));
				return GF_NOT_SUPPORTED;
#endif
			}
		}


		flag = gf_bs_read_int(bs, 1);
		if (!flag) {

			if (field->fieldType != GF_SG_VRML_MFNODE) {
				e = gf_sg_vrml_mf_reset(field->far_ptr, field->fieldType);
				if (e) return e;
			}

			flag = gf_bs_read_int(bs, 1);
			if (flag) {
				e = BD_DecMFFieldList(codec, bs, node, field, is_mem_com);
			} else {
				e = BD_DecMFFieldVec(codec, bs, node, field, is_mem_com);
			}
			if (e) return codec->LastError = e;
		}
	}
	return GF_OK;
}
