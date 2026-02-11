position_strand_distro_anomaly_lrt(const double alpha,
                                   const snp_pos_info& pi) {

    double null_loghood(0);
    double alt_loghood(0);
    unsigned df(0);
    position_strand_distro_anomaly_lrt_expert(pi,null_loghood,alt_loghood,df);
    if (df == 0) return false;

    return is_lrt_reject_null(null_loghood,alt_loghood,df,alpha);
}
