ms_escher_read_OPT (MSEscherState *state, MSEscherHeader *h)
{
	int const num_properties = h->instance;
	gboolean needs_free;
	guint8 const *data = ms_escher_get_data (state,
		h->offset + COMMON_HEADER_LEN, h->len - COMMON_HEADER_LEN, &needs_free);
	guint8 const *fopte = data;
	guint8 const *extra = fopte + 6*num_properties;
	guint prev_pid = 0;
	char const *name;
	int i;


	g_return_val_if_fail (6*num_properties + COMMON_HEADER_LEN <= h->len, TRUE);
	g_return_val_if_fail (data != NULL, TRUE);

	for (i = 0; i < num_properties; ++i, fopte += 6) {
		guint16 const tmp = GSF_LE_GET_GUINT32(fopte);
		guint const pid = tmp & 0x3fff;
		gboolean const is_blip = (tmp & 0x4000) != 0;
		gboolean const is_complex = (tmp & 0x8000) != 0;
		guint32 val = GSF_LE_GET_GUINT32 (fopte+2);
		MSObjAttrID id = MS_OBJ_ATTR_NONE;


		if (prev_pid >= pid) {
			g_printerr ("Pids not monotonic %d >= %d;\n", prev_pid, pid);
			if (needs_free)
				g_free ((guint8 *)data);
			return TRUE;
		}
		prev_pid = pid;

		name = NULL;
		switch (pid) {


		case 4 : name = "long rotation"; break;


		case 119 : case 120 : case 121 : case 122 : case 123 :
		case 124 : case 125 : case 126 : case 127 :
			ms_escher_read_OPT_bools (h,
				protection_bools, G_N_ELEMENTS (protection_bools),
				pid, val);
			break;


		case 128 : name = "long Txid"; break;

		case 129 : name = "long dxTextLeft"; break;

		case 130 : name = "long dyTextTop"; break;

		case 131 : name = "long dxTextRight"; break;

		case 132 : name = "long dyTextBottom"; break;

		case 133 : name = "WrapMode wrap_text_at_margin"; break;

		case 134 : name = "long scaleText"; break;

		case 135 : name = "AnchorType anchorText"; break;

		case 136 : name = "TextFlow txflTextFlow"; break;

		case 137 : name = "RotationType cdirFont"; break;

		case 138 : name = "MSOHSP hspNext"; break;

		case 139 : name = "TextDirection txdir"; break;

		case 187 : case 188 : case 189 : case 190 : case 191 :
			ms_escher_read_OPT_bools (h,
				text_bools, G_N_ELEMENTS (text_bools),
				pid, val);
			break;


		case 192 : name = "wchar* gtextUNICODE"; break;

		case 193 : name = "char* gtextRTF"; break;

		case 194 : name = "Alignment gtextAlign"; break;

		case 195 : name = "long gtextSize"; break;

		case 196 : name = "long gtextSpacing"; break;

		case 197 : name = "wchar* gtextFont"; break;

		case 240 : case 241 : case 242 : case 243 : case 244 :
		case 245 : case 246 : case 247 : case 248 : case 249 :
		case 250 : case 251 : case 252 : case 253 : case 254 :
		case 255 :
			ms_escher_read_OPT_bools (h,
				geotext_bools, G_N_ELEMENTS (geotext_bools),
				pid, val);
			break;


		case 256 : name = "fixed16_16 cropFromTop";
			   id = MS_OBJ_ATTR_BLIP_CROP_TOP;
			   break;
		case 257 : name = "fixed16_16 cropFromBottom";
			   id = MS_OBJ_ATTR_BLIP_CROP_BOTTOM;
			   break;
		case 258 : name = "fixed16_16 cropFromLeft";
			   id = MS_OBJ_ATTR_BLIP_CROP_LEFT;
			   break;
		case 259 : name = "fixed16_16 cropFromRight";
			   id = MS_OBJ_ATTR_BLIP_CROP_RIGHT;
			   break;


		case 260 : id = MS_OBJ_ATTR_BLIP_ID;
			   name = "Blip * pib";
			   break;


		case 261 : name = "wchar * pibName"; break;


		case 262 : name = "BlipType pibFlags"; break;

		case 263 : name = "long pictureTransparent"; break;

		case 264 : name = "long pictureContrast"; break;

		case 265 : name = "long pictureBrightness"; break;

		case 266 : name = "fixed16_16 pictureGamma"; break;

		case 267 : name = "Long pictureId"; break;

		case 268 : name = "Colour pictureDblCrMod"; break;

		case 269 : name = "Colour pictureFillCrMod"; break;

		case 270 : name = "Colour pictureLineCrMod"; break;

		case 271 : name = "Blip * pibPrint"; break;

		case 272 : name = "wchar * pibPrintName"; break;

		case 273 : name = "BlipType pibPrintFlags"; break;

		case 316 : case 317 : case 318 : case 319 :
			ms_escher_read_OPT_bools (h,
				picture_bools, G_N_ELEMENTS (picture_bools),
				pid, val);
			break;


		case 320 : name = "long geoLeft"; break;

		case 321 : name = "long geoTop"; break;

		case 322 : name = "long geoRight"; break;

		case 323 : name = "long geoBottom"; break;

		case 324 : name = "ShapePath shapePath"; break;

		case 325 : name = "IMsoArray pVertices"; break;

		case 326 : name = "IMsoArray pSegmentInfo"; break;


		case 327 : name = "long adjustValue"; break;

		case 328 : name = "long adjust2Value"; break;

		case 329 : name = "long adjust3Value"; break;

		case 330 : name = "long adjust4Value"; break;

		case 331 : name = "long adjust5Value"; break;

		case 332 : name = "long adjust6Value"; break;

		case 333 : name = "long adjust7Value"; break;

		case 334 : name = "long adjust8Value"; break;

		case 335 : name = "long adjust9Value"; break;

		case 336 : name = "long adjust10Value"; break;

		case 378 : case 379 : case 380 : case 381 : case 382 :
		case 383 :
			ms_escher_read_OPT_bools (h,
				geometry_bools, G_N_ELEMENTS (geometry_bools),
				pid, val);
			break;


		case 384 : id = MS_OBJ_ATTR_FILL_TYPE;
			   name = "FillType fillType";
			   break;


		case 385 : id = MS_OBJ_ATTR_FILL_COLOR;
			   name = "Colour fillColor";
			   break;


		case 386 : id = MS_OBJ_ATTR_FILL_ALPHA;
			   name = "long fillOpacity";
			   break;

		case 387 : id = MS_OBJ_ATTR_FILL_BACKGROUND;
			   name = "Colour fillBackColor";
			   break;

		case 388 : id = MS_OBJ_ATTR_FILL_BACKGROUND_ALPHA;
			   name = "long fillBackOpacity";
			   break;

		case 389 : name = "Colour fillCrMod"; break;

		case 390 : name = "IMsoBlip* fillBlip"; break;

		case 391 : name = "wchar* fillBlipName"; break;

		case 392 : name = "BlipFlags fillBlipFlags"; break;

		case 393 : name = "long fillWidth"; break;

		case 394 : name = "long fillHeight"; break;

		case 395 : id = MS_OBJ_ATTR_FILL_ANGLE;
			   name = "long fillAngle";
			   break;

		case 396 : id = MS_OBJ_ATTR_FILL_FOCUS;
			   name = "long fillFocus";
			   break;

		case 397 : name = "long fillToLeft"; break;

		case 398 : name = "long fillToTop"; break;

		case 399 : name = "long fillToRight"; break;

		case 400 : name = "long fillToBottom"; break;


		case 401 : name = "long fillRectLeft"; break;

		case 402 : name = "long fillRectTop"; break;

		case 403 : name = "long fillRectRight"; break;

		case 404 : name = "long fillRectBottom"; break;

		case 405 : name = "LengthMeasure fillDztype"; break;

		case 406 : id = MS_OBJ_ATTR_FILL_PRESET;
			   name = "long fillShadePreset";
			   break;

		case 407 : name = "IMsoArray fillShadeColors"; break;

		case 408 : name = "long fillOriginX"; break;

		case 409 : name = "long fillOriginY"; break;

		case 410 : name = "long fillShapeOriginX"; break;

		case 411 : name = "long fillShapeOriginY"; break;

		case 412 : id = MS_OBJ_ATTR_FILL_SHADE_TYPE;
			   name = "ShadeType fillShadeType";
			   break;

		case 443 : case 444 : case 445 : case 446 : case 447 :
			ms_escher_read_OPT_bools (h,
				fill_bools, G_N_ELEMENTS (fill_bools),
				pid, val);
			break;


		case 448 : id = MS_OBJ_ATTR_OUTLINE_COLOR;
			   name = "Colour lineColor";
			   break;

		case 449 : name = "long lineOpacity"; break;

		case 450 : name = "Colour lineBackColor"; break;

		case 451 : name = "Colour lineCrMod"; break;

		case 452 : name = "LineFill lineType"; break;

		case 453 : name = "IMsoBlip* lineFillBlip"; break;

		case 454 : name = "wchar* lineFillBlipName"; break;

		case 455 : name = "BlipFlags lineFillBlipFlags"; break;

		case 456 : name = "long lineFillWidth"; break;

		case 457 : name = "long lineFillHeight"; break;

		case 458 : name = "LengthMeasure lineFillDztype"; break;

		case 459 : id = MS_OBJ_ATTR_OUTLINE_WIDTH;
			   name = "long lineWidth";
			   val = val * 256. / 12700.;
			   break;

		case 460 : name = "long lineMiterLimit"; break;

		case 461 : name = "LineStyle lineStyle"; break;

		case 462 : id = MS_OBJ_ATTR_OUTLINE_STYLE;
			   name = "DashedLineStyle lineDashing";
			   break;

		case 463 : name = "IMsoArray lineDashStyle"; break;

		case 464 : id = MS_OBJ_ATTR_ARROW_START;
			   name = "LineEndStyle lineStartArrowhead";
			   break;

		case 465 : id = MS_OBJ_ATTR_ARROW_END;
			   name = "LineEndStyle lineEndArrowhead";
			   break;

		case 466 : id = MS_OBJ_ATTR_ARROW_START_WIDTH;
			   name = "ArrowWidth lineStartArrowWidth"; break;

		case 467 : id = MS_OBJ_ATTR_ARROW_START_LENGTH;
			   name = "ArrowLength lineStartArrowLength"; break;

		case 468 : id = MS_OBJ_ATTR_ARROW_END_WIDTH;
			   name = "ArrowWidth lineEndArrowWidth"; break;

		case 469 : id = MS_OBJ_ATTR_ARROW_END_LENGTH;
			   name = "ArrowLength lineEndArrowLength"; break;

		case 470 : name = "LineJoin lineJoinStyle"; break;

		case 471 : name = "LineCap lineEndCapStyle"; break;

		case 507 : case 508 : case 509 : case 510 : case 511 :
			ms_escher_read_OPT_bools (h,
				line_bools, G_N_ELEMENTS (line_bools),
				pid, val);
			break;


		case 512 : name = "Shadow shadowType"; break;

		case 513 : name = "Colour shadowColor"; break;

		case 514 : name = "Colour shadowHighlight"; break;

		case 515 : name = "Colour shadowCrMod"; break;

		case 516 : name = "long shadowOpacity"; break;

		case 517 : name = "long shadowOffsetX"; break;

		case 518 : name = "long shadowOffsetY"; break;

		case 519 : name = "long shadowSecondOffsetX"; break;

		case 520 : name = "long shadowSecondOffsetY"; break;

		case 521 : name = "long shadowScaleXToX"; break;

		case 522 : name = "long shadowScaleYToX"; break;

		case 523 : name = "long shadowScaleXToY"; break;

		case 524 : name = "long shadowScaleYToY"; break;

		case 525 : name = "long shadowPerspectiveX"; break;

		case 526 : name = "long shadowPerspectiveY"; break;

		case 527 : name = "long shadowWeight"; break;

		case 528 : name = "long shadowOriginX"; break;

		case 529 : name = "long shadowOriginY"; break;
		case 574 : case 575 :
			ms_escher_read_OPT_bools (h,
				shadow_bools, G_N_ELEMENTS (shadow_bools),
				pid, val);
			break;


		case 576 : name = "Transform perspectiveType"; break;


		case 577 : name = "long perspectiveOffsetX"; break;

		case 578 : name = "long perspectiveOffsetY"; break;

		case 579 : name = "long perspectiveScaleXToX"; break;

		case 580 : name = "long perspectiveScaleYToX"; break;

		case 581 : name = "long perspectiveScaleXToY"; break;

		case 582 : name = "long perspectiveScaleYToY"; break;

		case 583 : name = "long perspectivePerspectiveX"; break;

		case 584 : name = "long perspectivePerspectiveY"; break;

		case 585 : name = "long perspectiveWeight"; break;

		case 586 : name = "long perspectiveOriginX"; break;

		case 587 : name = "long perspectiveOriginY"; break;

		case 639 : name = "bool fPerspective"; break;


		case 640 : name = "long DSpecularAmt"; break;

		case 641 : name = "long c3DDiffuseAmt"; break;

		case 642 : name = "long c3DShininess"; break;

		case 643 : name = "long c3DEdgeThickness"; break;

		case 644 : name = "long c3DExtrudeForward"; break;

		case 645 : name = "long c3DExtrudeBackward"; break;

		case 646 : name = "long c3DExtrudePlane"; break;


		case 647 : name = "Colour c3DExtrusionColor"; break;

		case 648 : name = "Colour c3DCrMod"; break;
		case 700 : case 701 : case 702 : case 703 :
			ms_escher_read_OPT_bools (h,
				three_d_obj_bools, G_N_ELEMENTS (three_d_obj_bools),
				pid, val);
			break;


		case 704 : name = "long c3DYRotationAngle"; break;

		case 705 : name = "long c3DXRotationAngle"; break;

		case 706 : name = "long c3DRotationAxisX"; break;

		case 707 : name = "long c3DRotationAxisY"; break;

		case 708 : name = "long c3DRotationAxisZ"; break;

		case 709 : name = "long c3DRotationAngle"; break;

		case 710 : name = "long c3DRotationCenterX"; break;

		case 711 : name = "long c3DRotationCenterY"; break;

		case 712 : name = "long c3DRotationCenterZ"; break;

		case 713 : name = "RenderMode c3DRenderMode"; break;

		case 714 : name = "long c3DTolerance"; break;

		case 715 : name = "long c3DXViewpoint"; break;

		case 716 : name = "long c3DYViewpoint"; break;

		case 717 : name = "long c3DZViewpoint"; break;

		case 718 : name = "long c3DOriginX"; break;

		case 719 : name = "long c3DOriginY"; break;

		case 720 : name = "long c3DSkewAngle"; break;

		case 721 : name = "long c3DSkewAmount"; break;

		case 722 : name = "long c3DAmbientIntensity"; break;

		case 723 : name = "long c3DKeyX"; break;

		case 724 : name = "long c3DKeyY"; break;

		case 725 : name = "long c3DKeyZ"; break;

		case 726 : name = "long c3DKeyIntensity"; break;

		case 727 : name = "long c3DFillX"; break;

		case 728 : name = "long c3DFillY"; break;

		case 729 : name = "long c3DFillZ"; break;

		case 730 : name = "long c3DFillIntensity"; break;

		case 763 : case 764 : case 765 : case 766 : case 767 :
			ms_escher_read_OPT_bools (h,
				three_d_style_bools, G_N_ELEMENTS (three_d_style_bools),
				pid, val);
			break;


		case 769 : name = "MSOHSP pMaster"; break;

		case 771 : name = "ConnectStyle"; break;


		case 772 : name = "BlackWhiteMode bWMode"; break;

		case 773 : name = "BlackWhiteMode bWModePureBW"; break;

		case 774 : name = "BlackWhiteMode bWModeBW"; break;
		case 826 : case 827 : case 828 : case 830 : case 831 :
			ms_escher_read_OPT_bools (h,
				shape_bools, G_N_ELEMENTS (shape_bools),
				pid, val);
			break;


		case 832 : name = "CalloutType spcot"; break;

		case 833 : name = "long dxyCalloutGap"; break;

		case 834 : name = "CallOutAngle spcoa"; break;

		case 835 : name = "CalloutDrop spcod"; break;

		case 836 : name = "long dxyCalloutDropSpecified"; break;

		case 837 : name = "long dxyCalloutLengthSpecified"; break;

		case 889 : case 890 : case 891 : case 892 : case 893 :
		case 894 : case 895 :
			ms_escher_read_OPT_bools (h,
				callout_bools, G_N_ELEMENTS (callout_bools),
				pid, val);
			break;


		case 896 : id = MS_OBJ_ATTR_OBJ_NAME;
			   name = "wchar* wzName";
			   break;

		case 897 : id = MS_OBJ_ATTR_OBJ_ALT_TEXT;
			   name = "wchar* wzDescription";
			   break;


		case 898 : name = "IHlink* pihlShape"; break;

		case 899 : name = "IMsoArray pWrapPolygonVertices"; break;

		case 900 : name = "long dxWrapDistLeft"; break;

		case 901 : name = "long dyWrapDistTop"; break;

		case 902 : name = "long dxWrapDistRight"; break;

		case 903 : name = "long dyWrapDistBottom"; break;

		case 904 : name = "long lidRegroup"; break;

		case 953 : case 954 : case 955 : case 956 : case 957 :
		case 958 : case 959 :
			ms_escher_read_OPT_bools (h,
				group_bools, G_N_ELEMENTS (group_bools),
				pid, val);
			break;

		default : name = "UnknownID";
		}

		d (0, {
			if (NULL != name)
				   g_printerr ("%s %d = 0x%08x (=%d) %s%s;\n", name, pid, val, val,
			      is_blip ? " is blip" : "",
					   is_complex ? " is complex" : "");
		});


		if (is_complex) {

			g_return_val_if_fail (extra + val - data + COMMON_HEADER_LEN <= h->len, TRUE);

			d (5, gsf_mem_dump (extra, val););
			d (11, {
				static int count = 0;
				char *name = g_strdup_printf ("gnumeric-complex-opt-[%d]-%d", pid, count++);
				FILE *f = g_fopen (name, "w");
				if (f != NULL) {
					fwrite (extra, 1, val, f);
					fclose (f);
				}
				g_free (name);
			});
			if (id & MS_OBJ_ATTR_IS_PTR_MASK) {
				char *s = g_utf16_to_utf8 ((gunichar2*)extra, val / 2,
							   NULL, NULL, NULL);
				ms_escher_header_add_attr (h,
					ms_obj_attr_new_ptr (id, s));
				id = MS_OBJ_ATTR_NONE;
			}
			extra += val;
		}

		if (id & MS_OBJ_ATTR_IS_INT_MASK)
			ms_escher_header_add_attr (h,
				ms_obj_attr_new_uint (id, val));
		else if (id != MS_OBJ_ATTR_NONE) {
			g_warning ("We know attr[%d] with id == 0x%x, but do not store it ?", pid, id);
		}
	}
	if (needs_free)
		g_free ((guint8 *)data);

	return FALSE;
}
