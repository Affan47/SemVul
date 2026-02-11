find_proc_in_array(vmon_t *vmon, vmon_proc_t *proc, int hint)
{
	int	ret = -1;

	if(hint >= 0 && hint < vmon->array_allocated_nr && vmon->array[hint] == proc) {

		ret = hint;
	} else {
		int	i;


		for(i = 0; i < vmon->array_allocated_nr; i++) {
			if(vmon->array[i] == proc) {
				ret = i;
				break;
			}
		}
	}

	if(!proc && ret == -1) {
		vmon_proc_t	**tmp;


		tmp = realloc(vmon->array, (vmon->array_allocated_nr + VMON_ARRAY_GROWBY) * sizeof(vmon_proc_t *));
		if(tmp) {
			memset(&tmp[vmon->array_allocated_nr], 0, VMON_ARRAY_GROWBY * sizeof(vmon_proc_t *));
			ret = vmon->array_hint_free = vmon->array_allocated_nr;
			vmon->array_allocated_nr += VMON_ARRAY_GROWBY;
			vmon->array = tmp;
		}
	}

	return ret;
}
