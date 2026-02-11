__find_vcc(struct he_dev *he_dev, unsigned cid)
{
	struct hlist_head *head;
	struct atm_vcc *vcc;
	struct sock *s;
	short vpi;
	int vci;

	vpi = cid >> he_dev->vcibits;
	vci = cid & ((1 << he_dev->vcibits) - 1);
	head = &vcc_hash[vci & (VCC_HTABLE_SIZE -1)];

	sk_for_each(s, head) {
		vcc = atm_sk(s);
		if (vcc->dev == he_dev->atm_dev &&
		    vcc->vci == vci && vcc->vpi == vpi &&
		    vcc->qos.rxtp.traffic_class != ATM_NONE) {
				return vcc;
		}
	}
	return NULL;
}
