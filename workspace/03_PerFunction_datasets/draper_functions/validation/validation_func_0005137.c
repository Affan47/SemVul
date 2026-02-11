next_active_rdev(struct md_rdev *rdev, struct mddev *mddev)
{


	rcu_read_lock();
	if (rdev == NULL)

		rdev = list_entry(&mddev->disks, struct md_rdev, same_set);
	else {

		rdev_dec_pending(rdev, mddev);
	}
	list_for_each_entry_continue_rcu(rdev, &mddev->disks, same_set) {
		if (rdev->raid_disk >= 0 &&
		    !test_bit(Faulty, &rdev->flags)) {

			atomic_inc(&rdev->nr_pending);
			rcu_read_unlock();
			return rdev;
		}
	}
	rcu_read_unlock();
	return NULL;
}
