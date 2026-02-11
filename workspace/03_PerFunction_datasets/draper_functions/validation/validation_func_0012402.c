ht_copy_and_clear (cpp_reader *r ATTRIBUTE_UNUSED, hashnode hp, const void *ht2_p)
{
  cpp_hashnode *h = CPP_HASHNODE (hp);
  struct ht *ht2 = (struct ht *) ht2_p;

  if (h->type != NT_VOID
      && (h->flags & NODE_BUILTIN) == 0)
    {
      cpp_hashnode *h2 = CPP_HASHNODE (ht_lookup (ht2,
						  NODE_NAME (h),
						  NODE_LEN (h),
						  HT_ALLOC));
      h2->type = h->type;
      memcpy (&h2->value, &h->value, sizeof (h->value));

      h->type = NT_VOID;
      memset (&h->value, 0, sizeof (h->value));
    }
  return 1;
}
