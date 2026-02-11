SeenVariableDefinition(char* name,char* type,int scope)
{
 Variable var;
 int seen=0;

#if DEBUG
 printf("#Var.c# Variable definition for '%s'\n",name);
#endif

 for(var=CurFile->variables;var;var=var->next)
    if(!strcmp(var->name,name))
      {
       var->scope|=scope;
       seen=1;
       if(!in_header && var->scope&EXTERN_H)
         {
          if(var->comment)
             Free(var->comment);
          var->comment=MallocString(GetCurrentComment());
          var->lineno=parse_line;
         }
       break;
      }

 if(!seen)
   {
    var=NewVariableType(name,type);

    var->comment=MallocString(GetCurrentComment());
    var->scope=scope;

    var->lineno=parse_line;

    if(in_header && !(scope&EXTERN_H))
       var->incfrom=MallocString(parse_file);

    AddToLinkedList(CurFile->variables,Variable,var);
   }
}
