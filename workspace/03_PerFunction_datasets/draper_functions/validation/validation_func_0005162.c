setStatusMessage(UT_UCSChar * pBufUCS, int )
{
    if(getFrame()->getFrameMode() != XAP_NormalFrame)
    {
	return;
    }
    m_sStatusMessage.clear();

    if (pBufUCS && *pBufUCS)
	m_sStatusMessage.appendUCS4(pBufUCS);

    ap_sbf_StatusMessage * pf = static_cast<ap_sbf_StatusMessage *>(m_pStatusMessageField);
    if(pf)
	pf->update(m_sStatusMessage);
}
