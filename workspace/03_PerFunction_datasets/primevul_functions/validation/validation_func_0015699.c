int hci_get_random_address(struct hci_dev *hdev, bool require_privacy,
			   bool use_rpa, struct adv_info *adv_instance,
			   u8 *own_addr_type, bdaddr_t *rand_addr)
{
	int err;

	bacpy(rand_addr, BDADDR_ANY);


	if (use_rpa) {
		int to;


		if (use_ll_privacy(hdev))
			*own_addr_type = ADDR_LE_DEV_RANDOM_RESOLVED;
		else
			*own_addr_type = ADDR_LE_DEV_RANDOM;

		if (adv_instance) {
			if (!adv_instance->rpa_expired &&
			    !bacmp(&adv_instance->random_addr, &hdev->rpa))
				return 0;

			adv_instance->rpa_expired = false;
		} else {
			if (!hci_dev_test_and_clear_flag(hdev, HCI_RPA_EXPIRED) &&
			    !bacmp(&hdev->random_addr, &hdev->rpa))
				return 0;
		}

		err = smp_generate_rpa(hdev, hdev->irk, &hdev->rpa);
		if (err < 0) {
			bt_dev_err(hdev, "failed to generate new RPA");
			return err;
		}

		bacpy(rand_addr, &hdev->rpa);

		to = msecs_to_jiffies(hdev->rpa_timeout * 1000);
		if (adv_instance)
			queue_delayed_work(hdev->workqueue,
					   &adv_instance->rpa_expired_cb, to);
		else
			queue_delayed_work(hdev->workqueue,
					   &hdev->rpa_expired, to);

		return 0;
	}


	if (require_privacy) {
		bdaddr_t nrpa;

		while (true) {


			get_random_bytes(&nrpa, 6);
			nrpa.b[5] &= 0x3f;


			if (bacmp(&hdev->bdaddr, &nrpa))
				break;
		}

		*own_addr_type = ADDR_LE_DEV_RANDOM;
		bacpy(rand_addr, &nrpa);

		return 0;
	}


	*own_addr_type = ADDR_LE_DEV_PUBLIC;

	return 0;
}
