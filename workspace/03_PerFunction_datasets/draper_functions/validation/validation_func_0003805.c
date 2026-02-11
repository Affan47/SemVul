ompi_group_range_excl(ompi_group_t* group, int n_triplets, int ranges[][3],
                          ompi_group_t **new_group)
{

    int j,k,i;
    int *ranks_included=NULL, *ranks_excluded=NULL;
    int index,first_rank,last_rank,stride,count,result;

    count = 0;


    k = 0;
    for(j=0 ; j<n_triplets ; j++) {
        first_rank = ranges[j][0];
        last_rank = ranges[j][1];
        stride = ranges[j][2];

        if (first_rank < last_rank) {

            index = first_rank;
            while (index <= last_rank) {
                count ++;
                index += stride;
            }
        }
        else if (first_rank > last_rank) {

            index = first_rank;
            while (index >= last_rank) {
                count ++;
                index += stride;
            }

        } else {
            index = first_rank;
            count ++;
        }
    }
    if (0 != count) {
        ranks_excluded = (int *)malloc( (count)*(sizeof(int)));
    }

    k = 0;
    i = 0;
    for(j=0 ; j<n_triplets ; j++) {
        first_rank = ranges[j][0];
        last_rank = ranges[j][1];
        stride = ranges[j][2];

        if (first_rank < last_rank) {

            index = first_rank;
            while (index <= last_rank) {
                ranks_excluded[i] = index;
                i++;
                index += stride;
            }
        }
        else if (first_rank > last_rank) {

            index = first_rank;
            while (index >= last_rank) {
                ranks_excluded[i] = index;
                i++;
                index += stride;
            }

        } else {
            index = first_rank;
            ranks_excluded[i] = index;
            i++;
        }
    }
    if (0 != (group->grp_proc_count - count)) {
        ranks_included = (int *)malloc( (group->grp_proc_count - count)*(sizeof(int)));
    }
    for (j=0 ; j<group->grp_proc_count ; j++) {
        for(index=0 ; index<i ; index++) {
            if(ranks_excluded[index] == j) break;
        }
        if (index == i) {
            ranks_included[k] = j;
            k++;
        }
    }
    if (NULL != ranks_excluded) {
        free(ranks_excluded);
    }

    result = ompi_group_incl(group, k, ranks_included, new_group);

    if (NULL != ranks_included) {
        free(ranks_included);
    }

    return result;
}
