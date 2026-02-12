static int snd_ctl_elem_add(struct snd_ctl_file *file,
			    struct snd_ctl_elem_info *info, int replace)
{
	struct snd_card *card = file->card;
	struct snd_kcontrol *kctl;
	unsigned int count;
	unsigned int access;
	long private_size;
	size_t alloc_size;
	struct user_element *ue;
	unsigned int offset;
	int err;

	if (!*info->id.name)
		return -EINVAL;
	if (strnlen(info->id.name, sizeof(info->id.name)) >= sizeof(info->id.name))
		return -EINVAL;


	if (replace) {
		info->id.numid = 0;
		err = snd_ctl_remove_user_ctl(file, &info->id);
		if (err)
			return err;
	}


	count = info->owner;
	if (count == 0)
		count = 1;


	access = info->access;
	if (access == 0)
		access = SNDRV_CTL_ELEM_ACCESS_READWRITE;
	access &= (SNDRV_CTL_ELEM_ACCESS_READWRITE |
		   SNDRV_CTL_ELEM_ACCESS_INACTIVE |
		   SNDRV_CTL_ELEM_ACCESS_TLV_WRITE);


	if (access & SNDRV_CTL_ELEM_ACCESS_TLV_WRITE)
		access |= SNDRV_CTL_ELEM_ACCESS_TLV_CALLBACK;
	access |= SNDRV_CTL_ELEM_ACCESS_USER;


	err = snd_ctl_check_elem_info(NULL, info);
	if (err < 0)
		return err;

	if (info->count < 1)
		return -EINVAL;
	private_size = value_sizes[info->type] * info->count;
	alloc_size = compute_user_elem_size(private_size, count);

	down_write(&card->controls_rwsem);
	if (check_user_elem_overflow(card, alloc_size)) {
		err = -ENOMEM;
		goto unlock;
	}


	err = snd_ctl_new(&kctl, count, access, file);
	if (err < 0)
		goto unlock;
	memcpy(&kctl->id, &info->id, sizeof(kctl->id));
	ue = kzalloc(alloc_size, GFP_KERNEL);
	if (!ue) {
		kfree(kctl);
		err = -ENOMEM;
		goto unlock;
	}
	kctl->private_data = ue;
	kctl->private_free = snd_ctl_elem_user_free;


	card->user_ctl_alloc_size += alloc_size;


	ue->card = card;
	ue->info = *info;
	ue->info.access = 0;
	ue->elem_data = (char *)ue + sizeof(*ue);
	ue->elem_data_size = private_size;
	if (ue->info.type == SNDRV_CTL_ELEM_TYPE_ENUMERATED) {
		err = snd_ctl_elem_init_enum_names(ue);
		if (err < 0) {
			snd_ctl_free_one(kctl);
			goto unlock;
		}
	}


	if (info->type == SNDRV_CTL_ELEM_TYPE_ENUMERATED)
		kctl->info = snd_ctl_elem_user_enum_info;
	else
		kctl->info = snd_ctl_elem_user_info;
	if (access & SNDRV_CTL_ELEM_ACCESS_READ)
		kctl->get = snd_ctl_elem_user_get;
	if (access & SNDRV_CTL_ELEM_ACCESS_WRITE)
		kctl->put = snd_ctl_elem_user_put;
	if (access & SNDRV_CTL_ELEM_ACCESS_TLV_WRITE)
		kctl->tlv.c = snd_ctl_elem_user_tlv;


	err = __snd_ctl_add_replace(card, kctl, CTL_ADD_EXCLUSIVE);
	if (err < 0) {
		snd_ctl_free_one(kctl);
		goto unlock;
	}
	offset = snd_ctl_get_ioff(kctl, &info->id);
	snd_ctl_build_ioff(&info->id, kctl, offset);


 unlock:
	up_write(&card->controls_rwsem);
	return err;
}
