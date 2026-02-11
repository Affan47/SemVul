_print_banner(ostream *ostr) const{
  if (! _first_time) return;
  _first_time=false;


  if (!ostr) return;

  (*ostr) << "#-------------------------------------------------------------------------" << endl;
  (*ostr) << "# You are running the PxCone plugin for FastJet                           " << endl;
  (*ostr) << "# Original code by the Luis Del Pozo, David Ward and Michael H. Seymour   " << endl;
  (*ostr) << "# If you use this plugin, please cite                                     " << endl;
  (*ostr) << "#   M. H. Seymour and C. Tevlin, JHEP 0611 (2006) 052 [hep-ph/0609100].   " << endl;
  (*ostr) << "# in addition to the usual FastJet reference.                             " << endl;
  (*ostr) << "#-------------------------------------------------------------------------" << endl;


  ostr->flush();
}
