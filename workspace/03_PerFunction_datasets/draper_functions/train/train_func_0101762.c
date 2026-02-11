make_new_paragraph()
{
	CL_RichEdit_Paragraph * par = new CL_RichEdit_Paragraph( richedit->get_width() - bounds_width );
	pars.push_back( par );
}
