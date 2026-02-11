check_ci(struct sockaddr_atmpvc *pvc)
{
    LINK *lnk;
    TABLE *walk;
    int vci;

    lnk = find_link(pvc->sap_addr.itf);
    if (!lnk) return 0;
    if (pvc->sap_addr.vpi == ATM_VPI_ANY) pvc->sap_addr.vpi = 0;

    for (walk = lnk->table; walk; walk = walk->next)
	if (walk->in_vpi == pvc->sap_addr.vpi) break;
    if (walk && walk->in_vci == ATM_VCI_UNSPEC) return 0;
    if (pvc->sap_addr.vci == ATM_VCI_UNSPEC) return !walk;
    if (pvc->sap_addr.vci != ATM_VCI_ANY)
	return !vci_exists(lnk,pvc->sap_addr.vpi,pvc->sap_addr.vci);
    for (vci = ATM_NOT_RSV_VCI; vci < MAX_VCI; vci++)
	if (!vci_exists(lnk,pvc->sap_addr.vpi,vci)) {
	    pvc->sap_addr.vci = vci;
	    return 1;
	}
    return 0;
}
