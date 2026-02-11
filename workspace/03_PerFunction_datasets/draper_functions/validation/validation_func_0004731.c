lpfc_sli_config_mbox_opcode_get(struct lpfc_hba *phba, LPFC_MBOXQ_t *mbox)
{
	struct lpfc_mbx_sli4_config *sli4_cfg;
	union lpfc_sli4_cfg_shdr *cfg_shdr;

	if (mbox->u.mb.mbxCommand != MBX_SLI4_CONFIG)
		return LPFC_MBOX_OPCODE_NA;
	sli4_cfg = &mbox->u.mqe.un.sli4_config;


	if (bf_get(lpfc_mbox_hdr_emb, &sli4_cfg->header.cfg_mhdr)) {
		cfg_shdr = &mbox->u.mqe.un.sli4_config.header.cfg_shdr;
		return bf_get(lpfc_mbox_hdr_opcode, &cfg_shdr->request);
	}


	if (unlikely(!mbox->sge_array))
		return LPFC_MBOX_OPCODE_NA;
	cfg_shdr = (union lpfc_sli4_cfg_shdr *)mbox->sge_array->addr[0];
	return bf_get(lpfc_mbox_hdr_opcode, &cfg_shdr->request);
}
