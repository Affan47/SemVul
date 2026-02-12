void sort_directory(struct dir *dir)
{
	struct dir_ent *cur, *l1, *l2, *next;
	int len1, len2, stride = 1;

	if(dir->dir_count < 2)
		return;


	do {
		l2 = dir->dirs;
		cur = NULL;


		while(l2) {
			l1 = l2;
			for(len1 = 0; l2 && len1 < stride; len1 ++, l2 = l2->next);
			len2 = stride;


			while(len1 && l2 && len2) {
				if(strcmp(l1->name, l2->name) <= 0) {
					next = l1;
					l1 = l1->next;
					len1 --;
				} else {
					next = l2;
					l2 = l2->next;
					len2 --;
				}

				if(cur) {
					cur->next = next;
					cur = next;
				} else
					dir->dirs = cur = next;
			}


			for(; len1; len1 --, l1 = l1->next) {
				if(cur) {
					cur->next = l1;
					cur = l1;
				} else
					dir->dirs = cur = l1;
			}
			for(; l2 && len2; len2 --, l2 = l2->next) {
				if(cur) {
					cur->next = l2;
					cur = l2;
				} else
					dir->dirs = cur = l2;
			}
		}
		cur->next = NULL;
		stride = stride << 1;
	} while(stride < dir->dir_count);
}
