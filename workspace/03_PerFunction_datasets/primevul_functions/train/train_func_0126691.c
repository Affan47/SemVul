acl_ratelimit(const uschar *arg, int where, uschar **log_msgptr)
{
double limit, period, count;
uschar *ss;
uschar *key = NULL;
uschar *unique = NULL;
int sep = '/';
BOOL leaky = FALSE, strict = FALSE, readonly = FALSE;
BOOL noupdate = FALSE, badacl = FALSE;
int mode = RATE_PER_WHAT;
int old_pool, rc;
tree_node **anchor, *t;
open_db dbblock, *dbm;
int dbdb_size;
dbdata_ratelimit *dbd;
dbdata_ratelimit_unique *dbdb;
struct timeval tv;


if (!(sender_rate_limit = string_nextinlist(&arg, &sep, NULL, 0)))
  return ratelimit_error(log_msgptr, "sender rate limit not set");

limit = Ustrtod(sender_rate_limit, &ss);
if      (tolower(*ss) == 'k') { limit *= 1024.0; ss++; }
else if (tolower(*ss) == 'm') { limit *= 1024.0*1024.0; ss++; }
else if (tolower(*ss) == 'g') { limit *= 1024.0*1024.0*1024.0; ss++; }

if (limit < 0.0 || *ss != '\0')
  return ratelimit_error(log_msgptr,
    "\"%s\" is not a positive number", sender_rate_limit);


period = !(sender_rate_period = string_nextinlist(&arg, &sep, NULL, 0))
  ? -1.0 : readconf_readtime(sender_rate_period, 0, FALSE);
if (period <= 0.0)
  return ratelimit_error(log_msgptr,
    "\"%s\" is not a time value", sender_rate_period);


count = 1.0;


while ((ss = string_nextinlist(&arg, &sep, big_buffer, big_buffer_size)))
  {
  if (strcmpic(ss, US"leaky") == 0) leaky = TRUE;
  else if (strcmpic(ss, US"strict") == 0) strict = TRUE;
  else if (strcmpic(ss, US"noupdate") == 0) noupdate = TRUE;
  else if (strcmpic(ss, US"readonly") == 0) readonly = TRUE;
  else if (strcmpic(ss, US"per_cmd") == 0) RATE_SET(mode, PER_CMD);
  else if (strcmpic(ss, US"per_conn") == 0)
    {
    RATE_SET(mode, PER_CONN);
    if (where == ACL_WHERE_NOTSMTP || where == ACL_WHERE_NOTSMTP_START)
      badacl = TRUE;
    }
  else if (strcmpic(ss, US"per_mail") == 0)
    {
    RATE_SET(mode, PER_MAIL);
    if (where > ACL_WHERE_NOTSMTP) badacl = TRUE;
    }
  else if (strcmpic(ss, US"per_rcpt") == 0)
    {


    if (where == ACL_WHERE_RCPT)
      RATE_SET(mode, PER_RCPT);
    else if (where >= ACL_WHERE_PREDATA && where <= ACL_WHERE_NOTSMTP)
      RATE_SET(mode, PER_ALLRCPTS), count = (double)recipients_count;
    else if (where == ACL_WHERE_MAIL || where > ACL_WHERE_NOTSMTP)
      RATE_SET(mode, PER_RCPT), badacl = TRUE;
    }
  else if (strcmpic(ss, US"per_byte") == 0)
    {


    RATE_SET(mode, PER_MAIL);
    if (where > ACL_WHERE_NOTSMTP) badacl = TRUE;
    else count = message_size < 0 ? 0.0 : (double)message_size;
    }
  else if (strcmpic(ss, US"per_addr") == 0)
    {
    RATE_SET(mode, PER_RCPT);
    if (where != ACL_WHERE_RCPT) badacl = TRUE, unique = US"*";
    else unique = string_sprintf("%s@%s", deliver_localpart, deliver_domain);
    }
  else if (strncmpic(ss, US"count=", 6) == 0)
    {
    uschar *e;
    count = Ustrtod(ss+6, &e);
    if (count < 0.0 || *e != '\0')
      return ratelimit_error(log_msgptr, "\"%s\" is not a positive number", ss);
    }
  else if (strncmpic(ss, US"unique=", 7) == 0)
    unique = string_copy(ss + 7);
  else if (!key)
    key = string_copy(ss);
  else
    key = string_sprintf("%s/%s", key, ss);
  }


if (mode == RATE_PER_CLASH)
  return ratelimit_error(log_msgptr, "conflicting per_* options");
if (leaky + strict + readonly > 1)
  return ratelimit_error(log_msgptr, "conflicting update modes");
if (badacl && (leaky || strict) && !noupdate)
  return ratelimit_error(log_msgptr,
    "\"%s\" must not have /leaky or /strict option, or cannot be used in %s ACL",
    ratelimit_option_string[mode], acl_wherenames[where]);


if (noupdate) readonly = TRUE, leaky = strict = FALSE;
if (badacl) readonly = TRUE;
if (readonly) count = 0.0;
if (!strict && !readonly) leaky = TRUE;
if (mode == RATE_PER_WHAT) mode = RATE_PER_MAIL;


if (!key)
  key = !sender_host_address ? US"" : sender_host_address;

key = string_sprintf("%s/%s/%s%s",
  sender_rate_period,
  ratelimit_option_string[mode],
  unique == NULL ? "" : "unique/",
  key);

HDEBUG(D_acl)
  debug_printf_indent("ratelimit condition count=%.0f %.1f/%s\n", count, limit, key);


old_pool = store_pool;

if (readonly)
  anchor = &ratelimiters_cmd;
else switch(mode)
  {
  case RATE_PER_CONN:
    anchor = &ratelimiters_conn;
    store_pool = POOL_PERM;
    break;
  case RATE_PER_BYTE:
  case RATE_PER_MAIL:
  case RATE_PER_ALLRCPTS:
    anchor = &ratelimiters_mail;
    break;
  case RATE_PER_ADDR:
  case RATE_PER_CMD:
  case RATE_PER_RCPT:
    anchor = &ratelimiters_cmd;
    break;
  default:
    anchor = NULL;
    log_write(0, LOG_MAIN|LOG_PANIC_DIE,
      "internal ACL error: unknown ratelimit mode %d", mode);
    break;
  }

if ((t = tree_search(*anchor, key)))
  {
  dbd = t->data.ptr;

  rc = (dbd->rate < limit)? FAIL : OK;
  store_pool = old_pool;
  sender_rate = string_sprintf("%.1f", dbd->rate);
  HDEBUG(D_acl)
    debug_printf_indent("ratelimit found pre-computed rate %s\n", sender_rate);
  return rc;
  }


if (!(dbm = dbfn_open(US"ratelimit", O_RDWR, &dbblock, TRUE)))
  {
  store_pool = old_pool;
  sender_rate = NULL;
  HDEBUG(D_acl) debug_printf_indent("ratelimit database not available\n");
  *log_msgptr = US"ratelimit database not available";
  return DEFER;
  }
dbdb = dbfn_read_with_length(dbm, key, &dbdb_size);
dbd = NULL;

gettimeofday(&tv, NULL);

if (dbdb)
  {

  HDEBUG(D_acl) debug_printf_indent("ratelimit found key in database\n");
  dbd = &dbdb->dbd;


  if(unique && tv.tv_sec > dbdb->bloom_epoch + period)
    {
    HDEBUG(D_acl) debug_printf_indent("ratelimit discarding old Bloom filter\n");
    dbdb = NULL;
    }


  if(unique && dbdb_size < sizeof(*dbdb))
    {
    HDEBUG(D_acl) debug_printf_indent("ratelimit discarding undersize Bloom filter\n");
    dbdb = NULL;
    }
  }


if (!dbdb)
  {
  if (!unique)
    {

    HDEBUG(D_acl) debug_printf_indent("ratelimit creating new rate data block\n");
    dbdb_size = sizeof(*dbd);
    dbdb = store_get(dbdb_size);
    }
  else
    {
    int extra;
    HDEBUG(D_acl) debug_printf_indent("ratelimit creating new Bloom filter\n");


    extra = (int)limit * 2 - sizeof(dbdb->bloom);
    if (extra < 0) extra = 0;
    dbdb_size = sizeof(*dbdb) + extra;
    dbdb = store_get(dbdb_size);
    dbdb->bloom_epoch = tv.tv_sec;
    dbdb->bloom_size = sizeof(dbdb->bloom) + extra;
    memset(dbdb->bloom, 0, dbdb->bloom_size);


    if (dbd)
      {
      dbdb->dbd = *dbd;
      dbd = &dbdb->dbd;
      }
    }
  }


if (unique && !readonly)
  {


  BOOL seen;
  unsigned n, hash, hinc;
  uschar md5sum[16];
  md5 md5info;


  md5_start(&md5info);
  md5_end(&md5info, unique, Ustrlen(unique), md5sum);
  hash = md5sum[0] | md5sum[1] << 8 | md5sum[2] << 16 | md5sum[3] << 24;
  hinc = md5sum[4] | md5sum[5] << 8 | md5sum[6] << 16 | md5sum[7] << 24;


  HDEBUG(D_acl) debug_printf_indent("ratelimit checking uniqueness of %s\n", unique);

  seen = TRUE;
  for (n = 0; n < 8; n++, hash += hinc)
    {
    int bit = 1 << (hash % 8);
    int byte = (hash / 8) % dbdb->bloom_size;
    if ((dbdb->bloom[byte] & bit) == 0)
      {
      dbdb->bloom[byte] |= bit;
      seen = FALSE;
      }
    }


  if (seen)
    {
    HDEBUG(D_acl) debug_printf_indent("ratelimit event found in Bloom filter\n");
    count = 0.0;
    }
  else
    HDEBUG(D_acl) debug_printf_indent("ratelimit event added to Bloom filter\n");
  }


if (!dbd)
  {
  HDEBUG(D_acl) debug_printf_indent("ratelimit initializing new key's rate data\n");
  dbd = &dbdb->dbd;
  dbd->time_stamp = tv.tv_sec;
  dbd->time_usec = tv.tv_usec;
  dbd->rate = count;
  }
else
  {


  double this_time = (double)tv.tv_sec
                   + (double)tv.tv_usec / 1000000.0;
  double prev_time = (double)dbd->time_stamp
                   + (double)dbd->time_usec / 1000000.0;


  double interval = this_time - prev_time <= 0.0 ? 1e-9
                  : this_time - prev_time;

  double i_over_p = interval / period;
  double a = exp(-i_over_p);


  dbd->time_stamp = tv.tv_sec;
  dbd->time_usec = tv.tv_usec;
  dbd->rate = (1 - a) * count / i_over_p + a * dbd->rate;


  if (dbd->rate < count) dbd->rate = count;
  }


rc = dbd->rate < limit ? FAIL : OK;


if ((rc == FAIL && leaky) || strict)
  {
  dbfn_write(dbm, key, dbdb, dbdb_size);
  HDEBUG(D_acl) debug_printf_indent("ratelimit db updated\n");
  }
else
  {
  HDEBUG(D_acl) debug_printf_indent("ratelimit db not updated: %s\n",
    readonly? "readonly mode" : "over the limit, but leaky");
  }

dbfn_close(dbm);


t = store_get(sizeof(tree_node) + Ustrlen(key));
t->data.ptr = dbd;
Ustrcpy(t->name, key);
(void)tree_insertnode(anchor, t);


store_pool = old_pool;
sender_rate = string_sprintf("%.1f", dbd->rate);

HDEBUG(D_acl)
  debug_printf_indent("ratelimit computed rate %s\n", sender_rate);

return rc;
}
