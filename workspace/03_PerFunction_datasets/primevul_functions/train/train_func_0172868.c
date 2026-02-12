LBLIST get_logbook_hierarchy(void) {
   int i, j, n, m, flag;
   char str[1000], grpname[256], grpmembers[1000];
   LBLIST root, *pgrp;
   char grplist[MAX_N_LIST][NAME_LENGTH];


   root = xmalloc(sizeof(LBNODE));
   memset(root, 0, sizeof(LBNODE));


   for (i = n = 0;; i++) {
      if (!enumcfg("global", grpname, sizeof(grpname), grpmembers, sizeof(grpmembers), i))
         break;


      flag = 0;
      strlcpy(str, grpname, sizeof(str));
      str[9] = 0;
      if (strieq(str, "top group"))
         flag = 2;
      str[5] = 0;
      if (strieq(str, "group"))
         flag = 1;

      if (flag) {


         if (n == 0)
            root->member = xmalloc(sizeof(void *));
         else
            root->member = xrealloc(root->member, (n + 1) * sizeof(void *));
         root->member[n] = xmalloc(sizeof(LBNODE));

         if (strlen(grpname) < 7)
            strlcpy(root->member[n]->name, "Invalid group definition!", 256);
         else if (flag == 1)
            strlcpy(root->member[n]->name, grpname + 6, 256);
         else
            strlcpy(root->member[n]->name, grpname + 10, 256);

         m = strbreak(grpmembers, grplist, MAX_N_LIST, ",", FALSE);
         root->member[n]->n_members = m;

         root->member[n]->member = xcalloc(sizeof(void *), m);
         root->member[n]->n_members = m;
         for (j = 0; j < m; j++) {
            root->member[n]->member[j] = xcalloc(sizeof(LBNODE), 1);
            strlcpy(root->member[n]->member[j]->name, grplist[j], 256);
         }

         root->member[n]->is_top = (flag == 2);

         n++;
      }
   }

   root->n_members = n;


   for (i = 0; i < root->n_members; i++)
      if (root->member[i]) {

         for (j = 0; j < root->n_members; j++) {
            if (i != j && root->member[j] != NULL && (pgrp = get_subgroup(root->member[j],
                                                                          root->member[i]->name)) != NULL) {


               xfree(*pgrp);


               *pgrp = root->member[i];


               root->member[i] = NULL;

               break;
            }
         }
      }


   for (i = 0; i < root->n_members; i++)
      if (root->member[i] == NULL) {
         for (j = i + 1; j < root->n_members; j++)
            if (root->member[j])
               break;

         if (j < root->n_members && root->member[j]) {
            root->member[i] = root->member[j];
            root->member[j] = NULL;
         }
      }

   for (i = 0; i < root->n_members; i++)
      if (root->member[i] == NULL)
         break;
   if (i < root->n_members)
      root->n_members = i;

   if (n == 0) {
      for (n = 0; lb_list[n].name[0]; n++);


      root->member = xcalloc(n, sizeof(void *));
      root->n_members = n;

      for (i = 0; i < n; i++) {
         root->member[i] = xcalloc(1, sizeof(LBNODE));
         strlcpy(root->member[i]->name, lb_list[i].name, 256);
      }
   }

   return root;
}
