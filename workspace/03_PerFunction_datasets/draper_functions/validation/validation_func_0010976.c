insert_mapq_count(const pos_t pos,
                  const unsigned sample_no,
                  const uint8_t mapq) {

    if (! is_pos_reportable(pos)) return;

    _stageman.validate_new_pos_value(pos,STAGE::get_pileup_stage_no(_client_opt));

    sample(sample_no).bc_buff.insert_mapq_count(pos,mapq);
}
