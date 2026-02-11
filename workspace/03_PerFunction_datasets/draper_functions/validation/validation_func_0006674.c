xml_showpgsline(GthSA *sa, unsigned int indentlevel,
                            GtFile *outfp)
{
  unsigned long i, numofexons;
  gt_assert(sa);
  numofexons = gth_sa_num_of_exons(sa);
  gth_indent(outfp, indentlevel);
  gt_file_xprintf(outfp, "<PGS_line>\n");
  indentlevel++;
  gth_indent(outfp, indentlevel);
  gt_file_xprintf(outfp, "<gDNA gen_id=\"%s\" gen_strand=\"%c\"/>\n",
                     gth_sa_gen_id(sa), gth_sa_gen_strand_char(sa));
  gth_indent(outfp, indentlevel);
  if (gth_sa_alphatype(sa) == DNA_ALPHA) {
    gt_file_xprintf(outfp, "<rDNA rDNA_id=\"%s\" rDNA_strand=\"%c\"/>\n",
                       gth_sa_ref_id(sa), gth_sa_ref_strand_char(sa));
  }
  else {
    gt_file_xprintf(outfp, "<rProt rProt_id=\"%s\"/>\n",
                       gth_sa_ref_id(sa));
  }
  gth_indent(outfp, indentlevel);
  gt_file_xprintf(outfp, "<gDNA_exon_coordinates>\n");
  indentlevel++;

  for (i = 0; i < numofexons; i++) {
    gth_indent(outfp, indentlevel);
    gt_file_xprintf(outfp, "<exon e_start=\"%lu\" e_stop=\"%lu\"/>\n",
                    gth_sa_left_genomic_exon_border(sa, i),
                    gth_sa_right_genomic_exon_border(sa, i));
  }

  indentlevel--;
  gth_indent(outfp, indentlevel);
  gt_file_xprintf(outfp, "</gDNA_exon_coordinates>\n");
  indentlevel--;
  gth_indent(outfp, indentlevel);
  gt_file_xprintf(outfp, "</PGS_line>\n");
}
