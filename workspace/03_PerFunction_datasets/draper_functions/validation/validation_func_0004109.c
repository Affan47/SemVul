ATS_2d0_2e2_2e11_2contrib_2parcomb_2SATS_2posloc_2esats__tostrptr_location (ats_ptr_type arg0) {

ATSlocal (ats_ptr_type, tmp131) ;
ATSlocal (ats_ptr_type, tmp132) ;
ATSlocal (ats_ptr_type, tmp133) ;
ATSlocal (ats_bool_type, tmp134) ;

ATSlocal (ats_int_type, tmp136) ;
ATSlocal (ats_ptr_type, tmp137) ;


__ats_lab_ATS_2d0_2e2_2e11_2contrib_2parcomb_2SATS_2posloc_2esats__tostrptr_location:
tmp132 = atslib_tmpfile_err () ;
tmp133 = ats_selsin_mac(tmp132, atslab_1) ;
tmp134 = atspre_pgt (tmp133, atspre_null_ptr) ;
if (tmp134) {
 ATS_2d0_2e2_2e11_2contrib_2parcomb_2SATS_2posloc_2esats__fprint_location (ats_castfn_mac(ats_ptr_type, tmp133), arg0) ;
tmp136 = atslib_fseek_err (tmp133, 0l, SEEK_SET) ;
tmp137 = ATS_2d0_2e2_2e11_2prelude_2SATS_2filebas_2esats__input_line_vt (ats_castfn_mac(ats_ptr_type, tmp133)) ;
 atslib_fclose_exn (tmp133) ;
tmp131 = tmp137 ;
} else {
tmp131 = atspre_strptr_null () ;
}
return (tmp131) ;
}
