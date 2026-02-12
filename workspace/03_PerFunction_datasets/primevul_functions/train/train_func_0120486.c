resolve_unres_data_autodel_diff(struct unres_data *unres, uint32_t unres_i)
{
    struct lyd_node *next, *child, *parent;
    uint32_t i;

    for (i = 0; i < unres->diff_idx; ++i) {
        if (unres->diff->type[i] == LYD_DIFF_DELETED) {

            continue;
        }

        if (unres->diff->second[i] == unres->node[unres_i]) {


            unres_data_diff_rem(unres, i);

            return;
        } else {
            parent = unres->diff->second[i]->parent;
            while (parent && (parent != unres->node[unres_i])) {
                parent = parent->parent;
            }
            if (parent) {


                unres_data_diff_rem(unres, i);
                break;
            }

            LY_TREE_DFS_BEGIN(unres->diff->second[i]->parent, next, child) {
                if (child == unres->node[unres_i]) {


                    return;
                }

                LY_TREE_DFS_END(unres->diff->second[i]->parent, next, child);
            }
        }
    }


    unres_data_diff_new(unres, unres->node[unres_i], unres->node[unres_i]->parent, 0);
    lyd_unlink(unres->node[unres_i]);


    unres->node[unres_i] = NULL;
}
