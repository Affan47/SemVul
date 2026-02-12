void DcmSCP::findPresentationContext(const T_ASC_PresentationContextID presID,
                                     OFString &abstractSyntax,
                                     OFString &transferSyntax)
{
  transferSyntax.clear();
  abstractSyntax.clear();
  if (m_assoc == NULL)
    return;

  DUL_PRESENTATIONCONTEXT *pc;
  LST_HEAD **l;


  l = &m_assoc->params->DULparams.acceptedPresentationContext;
  pc = (DUL_PRESENTATIONCONTEXT*) LST_Head(l);
  (void)LST_Position(l, (LST_NODE*)pc);
  while (pc)
  {
     if (presID == pc->presentationContextID)
     {
       if (pc->result == ASC_P_ACCEPTANCE)
       {

         transferSyntax = pc->acceptedTransferSyntax;
         abstractSyntax = pc->abstractSyntax;
       }
       break;
     }
     pc = (DUL_PRESENTATIONCONTEXT*) LST_Next(l);
  }
}
