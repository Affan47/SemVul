print()
{
    int i;


    printf("**********************\n");
    printf("GRUPPENTABELLE:\n");
    for (i=0; i< length_of_group_tabs; i++)
        printf("%d  %d \n", i, group_tab[i]);

    printf("NON_GRUPPENTABELLE:\n");
    for (i=0; i< length_of_group_tabs; i++)
        printf("%d %d\n", i, non_group_tab[i]);

    printf("**********************\n");

}
