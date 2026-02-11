identrst_get_39 (ats_ref_type arg0, ats_ref_type arg1) {

ATSlocal (ats_ptr_type, tmp124) ;
ATSlocal (ats_char_type, tmp125) ;
ATSlocal (ats_bool_type, tmp126) ;
ATSlocal (ats_int_type, tmp127) ;
ATSlocal (ats_ptr_type, tmp128) ;

__ats_lab_identrst_get_39:
#line 420 "libatsdoc_atext.dats"
tmp125 = atspre_char_of_int (ats_ptrget_mac(ats_int_type, arg1)) ;
#line 422 "libatsdoc_atext.dats"
tmp126 = IDENTRST_test_37 (tmp125) ;
#line 422 "libatsdoc_atext.dats"
if (tmp126) {
#line 423 "libatsdoc_atext.dats"
tmp127 = ATS_2d0_2e2_2e11_2libatsdoc_2SATS_2libatsdoc_reader_2esats__reader_get_char (arg0) ;
#line 423 "libatsdoc_atext.dats"
ats_ptrget_mac(ats_int_type, arg1) = tmp127 ;
#line 425 "libatsdoc_atext.dats"
tmp128 = identrst_get_39 (arg0, arg1) ;
#line 425 "libatsdoc_atext.dats"
tmp124 = ATS_MALLOC(sizeof(anairiats_sum_3)) ;
ats_selptrset_mac(anairiats_sum_3, tmp124, atslab_0, tmp125) ;
ats_selptrset_mac(anairiats_sum_3, tmp124, atslab_1, tmp128) ;
} else {
#line 427 "libatsdoc_atext.dats"
tmp124 = (ats_sum_ptr_type)0 ;
}
return (tmp124) ;
}
