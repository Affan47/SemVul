void ogs_nas_5gs_nas_guti_to_mobility_identity_guti(
        ogs_nas_5gs_guti_t *nas_guti,
        ogs_nas_5gs_mobile_identity_guti_t *mobile_identity_guti)
{
    ogs_assert(nas_guti);
    ogs_assert(mobile_identity_guti);

    memset(mobile_identity_guti, 0, sizeof(*mobile_identity_guti));


    mobile_identity_guti->h.supi_format = 0xf;
    mobile_identity_guti->h.type = OGS_NAS_5GS_MOBILE_IDENTITY_GUTI;

    memcpy(&mobile_identity_guti->nas_plmn_id,
            &nas_guti->nas_plmn_id, OGS_PLMN_ID_LEN);
    memcpy(&mobile_identity_guti->amf_id,
            &nas_guti->amf_id, sizeof(ogs_amf_id_t));
    mobile_identity_guti->m_tmsi = htobe32(nas_guti->m_tmsi);
}
