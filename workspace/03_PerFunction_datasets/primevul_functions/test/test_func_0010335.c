read_macro_assignment(uschar *s)
{
uschar name[64];
int namelen = 0;
BOOL redef = FALSE;
macro_item *m;
macro_item *mlast = NULL;

while (isalnum(*s) || *s == '_')
  {
  if (namelen >= sizeof(name) - 1)
    log_write(0, LOG_PANIC_DIE|LOG_CONFIG_IN,
      "macro name too long (maximum is %d characters)", sizeof(name) - 1);
  name[namelen++] = *s++;
  }
name[namelen] = 0;

while (isspace(*s)) s++;
if (*s++ != '=')
  log_write(0, LOG_PANIC_DIE|LOG_CONFIG_IN, "malformed macro definition");

if (*s == '=')
  {
  redef = TRUE;
  s++;
  }
while (isspace(*s)) s++;


for (m = macros; m != NULL; m = m->next)
  {
  int len = Ustrlen(m->name);

  if (Ustrcmp(m->name, name) == 0)
    {
    if (!m->command_line && !redef)
      log_write(0, LOG_CONFIG|LOG_PANIC_DIE, "macro \"%s\" is already "
       "defined (use \"==\" if you want to redefine it", name);
    break;
    }

  if (len < namelen && Ustrstr(name, m->name) != NULL)
    log_write(0, LOG_CONFIG|LOG_PANIC_DIE, "\"%s\" cannot be defined as "
      "a macro because previously defined macro \"%s\" is a substring",
      name, m->name);


  mlast = m;
  }


if (m != NULL && m->command_line) return;


if (redef)
  {
  if (m == NULL)
    log_write(0, LOG_CONFIG|LOG_PANIC_DIE, "can't redefine an undefined macro "
      "\"%s\"", name);
  }


else
  {
  m = store_get(sizeof(macro_item) + namelen);
  if (macros == NULL) macros = m; else mlast->next = m;
  Ustrncpy(m->name, name, namelen);
  m->name[namelen] = 0;
  m->next = NULL;
  m->command_line = FALSE;
  }


m->replacement = string_copy(s);
}
