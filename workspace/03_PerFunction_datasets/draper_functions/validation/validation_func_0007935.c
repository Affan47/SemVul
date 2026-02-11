compute_non_coding( void )
{
  if ( _non_coding_computed ) return;
  _non_coding_computed = true;

  _nb_bases_in_0_CDS                  = 0;
  _nb_bases_in_0_functional_CDS       = 0;
  _nb_bases_in_0_non_functional_CDS   = 0;
  _nb_bases_in_0_RNA                  = 0;
  _nb_bases_in_0_coding_RNA           = 0;
  _nb_bases_in_0_non_coding_RNA       = 0;
  _nb_bases_in_neutral_regions        = 0;
  _nb_neutral_regions                 = 0;

  ae_list_node<ae_genetic_unit*>* gen_unit_node = _genetic_unit_list->get_first();
  ae_genetic_unit*  gen_unit = NULL;

  while ( gen_unit_node != NULL )
  {
    gen_unit = gen_unit_node->get_obj();

    _nb_bases_in_0_CDS                  += gen_unit->get_nb_bases_in_0_CDS();
    _nb_bases_in_0_functional_CDS       += gen_unit->get_nb_bases_in_0_functional_CDS();
    _nb_bases_in_0_non_functional_CDS   += gen_unit->get_nb_bases_in_0_non_functional_CDS();
    _nb_bases_in_0_RNA                  += gen_unit->get_nb_bases_in_0_RNA();
    _nb_bases_in_0_coding_RNA           += gen_unit->get_nb_bases_in_0_coding_RNA();
    _nb_bases_in_0_non_coding_RNA       += gen_unit->get_nb_bases_in_0_non_coding_RNA();
    _nb_bases_in_neutral_regions        += gen_unit->get_nb_bases_in_neutral_regions();
    _nb_neutral_regions                 += gen_unit->get_nb_neutral_regions();
    gen_unit_node = gen_unit_node->get_next();
  }
}
