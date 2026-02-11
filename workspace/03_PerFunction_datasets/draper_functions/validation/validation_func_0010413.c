generate_descr(ostream& os, Language lang) {
#else
void OMPRegion::generate_descr(ostream& os) {
#endif
  os << "struct ompregdescr omp_rd_" << id << " = {\n";
  os << "  \"" << name << "\", \"" << sub_name << "\", "
     << num_sections << ", \"" << file_name << "\", "
     << begin_first_line << ", " << begin_last_line << ", "
     << end_first_line << ", " << end_last_line << "\n};\n";
#ifdef OPARI_VT
  if (!(lang & L_FORTRAN)) {
    os << "int omp_pt_" << id << " = -1;\n";
    os << "#pragma omp threadprivate(omp_pt_" << id << ")\n";
  }
#endif
  os << "\n";

  if (descrs.size()) {
    ostream::fmtflags sav_os_flags = os.flags();

    os << "#define POMP_DLIST_" << setw(5) << setfill('0') << id
        << " shared(";
    for (set<int>::const_iterator it = descrs.begin();
      it != descrs.end(); ++it) {
      if (it != descrs.begin()) os << ",";
      os << "omp_rd_" << *it;
    }
#ifdef OPARI_VT
    os << ") copyin(";
    for (set<int>::const_iterator it = descrs.begin();
      it != descrs.end(); ++it) {
      if (it != descrs.begin()) os << ",";
      os << "omp_pt_" << *it;
    }
#endif
    os << ")\n\n";

    os.flags( sav_os_flags );
  }
}
