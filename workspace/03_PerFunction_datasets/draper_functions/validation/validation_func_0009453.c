pdf_start_charproc_accum(gx_device_pdf *pdev)
{
    pdf_char_proc_t *pcp;
    pdf_resource_t *pres;
    int code = pdf_enter_substream(pdev, resourceCharProc, gs_next_ids(pdev->memory, 1),
                                   &pres, false, pdev->CompressFonts);

    if (code < 0)
       return code;
    pcp = (pdf_char_proc_t *)pres;
    pcp->owner_fonts = NULL;
    return 0;
}
