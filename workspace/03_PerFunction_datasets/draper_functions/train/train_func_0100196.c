protgroup_reset(struct protgroup *group)
{
    if(group) {
	memset(group->group, 0,
	       group->nalloced * sizeof(struct protstream *));
	group->next_element = 0;
    }
}
