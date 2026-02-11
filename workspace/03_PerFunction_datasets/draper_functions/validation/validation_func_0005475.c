txt_sa_visitor_visit_sa(GthSAVisitor *sa_visitor, GthSA *sa)
{
  GthTxtSAVisitor *visitor = txt_sa_visitor_cast(sa_visitor);
  gt_assert(sa);
  show_spliced_alignment(sa, visitor->input, visitor->gs2out,
                         visitor->minintronlength, visitor->widthforgenpos,
                         visitor->showintronmaxlen, visitor->translationtable,
                         visitor->showseqnums, visitor->outfp);
}
