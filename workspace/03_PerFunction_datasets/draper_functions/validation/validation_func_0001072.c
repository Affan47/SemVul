convert_type4_image(gx_device_pdf *pdev, const gs_imager_state * pis,
                      const gs_matrix *pmat, const gs_image_common_t *pic,
                      const gs_int_rect * prect,
                      const gx_drawing_color * pdcolor,
                      const gx_clip_path * pcpath, gs_memory_t * mem,
                      gx_image_enum_common_t ** pinfo,
                      pdf_typed_image_context_t context, image_union_t *image,
                      cos_dict_t *pnamed)
{

    gx_drawing_color icolor;
    int code;

    pdev->image_mask_is_SMask = false;
    if (pdf_convert_image4_to_image1(pdev, pis, pdcolor,
                                     (const gs_image4_t *)pic,
                                     &image[0].type1, &icolor) >= 0) {
        gs_state *pgs = (gs_state *)gx_hld_get_gstate_ptr(pis);

        if (pgs == NULL)
            return_error(gs_error_unregistered);


        if (pnamed)
            cos_array_add_object(pdev->NI_stack, COS_OBJECT(pnamed));


        code = gs_gsave(pgs);
        if (code < 0)
            return code;

        code = gs_setcolorspace(pgs, ((const gs_image4_t *)pic)->ColorSpace);
        if (code < 0)
            return code;
        code = pdf_begin_typed_image(pdev, pis, pmat,
                                     (gs_image_common_t *)&image[0].type1,
                                     prect, &icolor, pcpath, mem,
                                     pinfo, context);
        if (code < 0)
            return code;
        return gs_grestore(pgs);
    }
    return 1;
}
