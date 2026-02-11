decrement_ref_count (FMTreeModel *model, TreeNode *node, int count)
{
	node->all_children_ref_count -= count;
	if (node->all_children_ref_count == 0) {
		schedule_monitoring_update (model);
	}
}
