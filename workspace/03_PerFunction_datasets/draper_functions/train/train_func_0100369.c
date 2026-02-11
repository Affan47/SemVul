get_starling_bam_region_string(const starling_options& opt,
                               const starling_deriv_options& dopt) {

    const int zsize(opt.max_indel_size);
    const pos_t begin_pos(std::max(0,dopt.report_range.begin_pos-zsize));
    const pos_t end_pos(dopt.report_range.end_pos+zsize);

    std::ostringstream bam_region_oss;
    bam_region_oss << opt.bam_seq_name << ':' << begin_pos+1 << '-' << end_pos;
    return bam_region_oss.str();
}
