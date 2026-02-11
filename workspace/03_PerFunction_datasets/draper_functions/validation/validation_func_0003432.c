ReCheckAllConstraints(struct Promise *pp)

{ struct Constraint *cp;
 char *sp,*handle = GetConstraint("handle",pp,CF_SCALAR);
  struct PromiseIdent *prid;
  struct Item *ptr;
  int in_class_any = false;

if (strcmp(pp->agentsubtype,"reports") == 0 && strcmp(pp->classes,"any") == 0)
   {
   char *cl = GetConstraint("ifvarclass",pp,CF_SCALAR);

   if (cl == NULL || strcmp(cl,"any") == 0)
      {
      in_class_any = true;
      }

   if (in_class_any)
      {
      CfOut(cf_error,"","reports promises may not be in class \'any\' - risk of a notification explosion");
      PromiseRef(cf_error,pp);
      }
   }


if (SHOWREPORTS)
   {
   NewPromiser(pp);
   }

if (!IsDefinedClass(pp->classes))
   {
   return;
   }

if (VarClassExcluded(pp,&sp))
   {
   return;
   }


if (handle)
   {
   if (!ThreadLock(cft_policy))
      {
      CfOut(cf_error, "", "!! Could not lock cft_policy in ReCheckAllConstraints() -- aborting");
      return;
      }

   if ((prid = PromiseIdExists(handle)))
      {
      if ((strcmp(prid->filename,pp->audit->filename) != 0) || (prid->lineno != pp->lineno))
         {
         CfOut(cf_error,""," !! Duplicate promise handle -- previously used in file %s near line %d",prid->filename,prid->lineno);
         PromiseRef(cf_error,pp);
         }
      }
   else
      {
      NewPromiseId(handle,pp);
      }

   prid = NULL;
   ThreadUnlock(cft_policy);
   }

if (REQUIRE_COMMENTS == true)
   {
   if (pp->ref == NULL && strcmp(pp->agentsubtype,"vars") != 0)
      {
      CfOut(cf_error,""," !! Un-commented promise found, but comments have been required by policy\n");
      PromiseRef(cf_error,pp);
      }
   }

for (cp = pp->conlist; cp != NULL; cp = cp->next)
   {
   PostCheckConstraint(pp->agentsubtype,pp->bundle,cp->lval,cp->rval,cp->type);
   }

if (strcmp(pp->agentsubtype,"insert_lines") == 0)
   {


   if ((sp = GetConstraint("select_line_matching",pp,CF_SCALAR)))
      {
      if ((ptr = ReturnItemIn(EDIT_ANCHORS,sp)))
         {
         if (strcmp(ptr->classes,pp->bundle) == 0)
            {
            CfOut(cf_inform,""," !! insert_lines promise uses the same select_line_matching anchor (\"%s\") as another promise. This will lead to non-convergent behaviour unless \"empty_file_before_editing\" is set.",sp);
            PromiseRef(cf_inform,pp);
            }
         }
      else
         {
         PrependItem(&EDIT_ANCHORS,sp,pp->bundle);
         }
      }
   }

PreSanitizePromise(pp);
}
