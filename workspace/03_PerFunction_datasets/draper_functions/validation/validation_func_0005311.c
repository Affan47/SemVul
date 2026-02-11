gt_ggc_mx_section (void *x_p)
{
  union section * const x = (union section *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      switch (SECTION_STYLE (&(((*x)))))
        {
        case SECTION_NAMED:
          gt_ggc_m_S ((*x).named.name);
          gt_ggc_m_9tree_node ((*x).named.decl);
          break;
        case SECTION_UNNAMED:
          gt_ggc_m_7section ((*x).unnamed.next);
          break;
        case SECTION_NOSWITCH:
          break;
        default:
          break;
        }
    }
}
