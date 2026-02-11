pdf_set_drawing_color(gx_device_pdf * pdev, const gs_imager_state * pis,
                      const gx_drawing_color *pdc,
                      gx_hl_saved_color * psc,
                      bool *used_process_color,
                      const psdf_set_color_commands_t *ppscc)
{
    gx_hl_saved_color temp;
    int code;


    if (pdev->skip_colors)
        return 0;
    gx_hld_save_color(pis, pdc, &temp);


    if (gx_hld_saved_color_equal(&temp, psc))
        return 0;


    code = pdf_open_page(pdev, PDF_IN_STREAM);
    if (code < 0)
        return code;

    return pdf_reset_color(pdev, pis, pdc, psc, used_process_color, ppscc);
}
