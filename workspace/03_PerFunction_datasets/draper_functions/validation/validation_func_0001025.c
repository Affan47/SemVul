fastjetppgenkt_(const double * p, const int & npart,
                     const double & R, const double & palg,
                     double * f77jets, int & njets) {


    if (palg == 1.0) {
      jet_def = JetDefinition(kt_algorithm, R);
    }  else if (palg == 0.0) {
      jet_def = JetDefinition(cambridge_algorithm, R);
    }  else if (palg == -1.0) {
      jet_def = JetDefinition(antikt_algorithm, R);
    } else {
      jet_def = JetDefinition(genkt_algorithm, R, palg);
    }


    transfer_cluster_transfer(p,npart,jet_def,f77jets,njets);
}
