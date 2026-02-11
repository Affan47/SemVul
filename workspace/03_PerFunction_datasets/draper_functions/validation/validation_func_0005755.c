check_mem_port_conflict_for_entry(List **bus,
                                  TE *entry,
                                  List *group,
                                  int bus_num)
{
    Boolean flg = FALSE;
    int i;

    for (i = 0; i < bus_number; i++) {
        if (i == bus_num) {
            continue;
        }
        if (entry->type == DTU_TRANS_LOAD
            || entry->type == DTU_TRANS_STORE) {
            if (!check_mem_port_for_csm(bus, bus_num, group->data,
                                        ((TG *)(group->data))->kickpe,
                                        entry->starttime, entry->cost)) {
                flg = TRUE;
            }
        } else if (entry->type == DTU_TRANS_SEND
                   || entry->type == DTU_TRANS_PULL) {
            if (!check_trans_src_dst_port(bus, bus_num, group->data,
                                          entry->srcpe, entry->dstpe,
                                          entry->starttime, entry->cost)) {
                flg = TRUE;
            }
        } else {
            fprintf(stderr,
                    "Unknown or Not Supported Transfer Type...\n");
            print_bus_state(bus);
            abort();
        }
    }
    if (flg) {
        fprintf(stderr,
                "Illegal DTU Transfer!! (Kicked by MT%d, MT%d -> MT%d)\n",
                ((TG *)(group->data))->kickmt, entry->srcmt, entry->dstmt);
        print_bus_state(bus);
        abort();
    }
}
