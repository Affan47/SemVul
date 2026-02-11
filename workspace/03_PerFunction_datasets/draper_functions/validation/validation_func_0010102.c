set_is_MM_instance(pdf_font_resource_t *pdfont, const gs_font_base *pfont)
{
    switch (pfont->FontType) {
    case ft_encrypted:
    case ft_encrypted2:
        pdfont->u.simple.s.type1.is_MM_instance =
            ((const gs_font_type1 *)pfont)->data.WeightVector.count > 0;
    default:
        break;
    }
}
