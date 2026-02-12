pdf_close_text_contents(gx_device_pdf *pdev)
{


    pdf_text_state_t *pts = pdev->text->text_state;

    pts->in.pdfont = pts->out.pdfont = 0;
    pts->in.size = pts->out.size = 0;
}
