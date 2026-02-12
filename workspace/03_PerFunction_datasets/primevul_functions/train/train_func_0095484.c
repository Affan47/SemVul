static void lsr_delete_anim_value(GF_LASeRCodec *lsr, SMIL_AnimateValue *val, u32 coded_type)
{

	switch (coded_type) {
	case 0:
		gf_free(* (SVG_String *)val->value);
		gf_free(val->value);
		break;
	case 1:
		gf_free(val->value);
		break;
	case 2:
		gf_svg_delete_attribute_value(SVG_PathData_datatype, val->value, NULL);
		break;
	case 3:
		gf_svg_delete_attribute_value(SVG_Points_datatype, val->value, NULL);
		break;
	case 4:
		gf_free(val->value);
		break;
	case 5:
		gf_free(val->value);
		break;
	case 6:
		gf_free(val->value);
		break;
	case 7:
	case 8:
		{
			GF_List *l = (GF_List *) val->value;
			while (gf_list_count(l)) {
				void *v = gf_list_pop_back(l);
				gf_free(v);
			}
			gf_list_del(l);
		}
		break;

	case 9:
		gf_free(val->value);
		break;
	case 10:
		gf_free(val->value);
		break;
	case 11:
	{
		SVG_FontFamily *ft = (SVG_FontFamily *) val->value;
		if (ft->value) gf_free(ft->value);
		gf_free(ft);
	}
		break;
	case 12:
	{
		XMLRI *iri = (XMLRI *)val->value;
		gf_list_del_item(lsr->deferred_hrefs, iri);
		gf_node_unregister_iri(lsr->sg, iri);
		if (iri->string) gf_free(iri->string);
		gf_free(iri);
	}
	default:
		break;
	}
	val->value = NULL;
}
