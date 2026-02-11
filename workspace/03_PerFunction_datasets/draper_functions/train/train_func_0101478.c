Handler_CSI(ccf_Context cc, int Code)
{
  switch (Code)
   {
   case 0x30:
   case 0x31:
   case 0x32:
   case 0x33:
   case 0x34:
   case 0x35:
   case 0x36:
   case 0x37:
   case 0x38:
   case 0x39:
     if (cc->i.csi.state > CSI_STATE_PARAMETER)
     break;
     cc->i.csi.state = CSI_STATE_PARAMETER;
     cc->i.csi.parameter[cc->i.csi.current] =
     cc->i.csi.parameter[cc->i.csi.current]*10 + Code-0x30;
     return;

   case 0x3A:
   case 0x3B:
     if (cc->i.csi.state > CSI_STATE_PARAMETER)
     break;
     cc->i.csi.state = CSI_STATE_PARAMETER;
     if (cc->i.csi.current < NumberOf(cc->i.csi.parameter)-1)
     ++cc->i.csi.current;
     cc->i.csi.parameter[cc->i.csi.current] = 0;
     return;
   case 0x3C:
   case 0x3D:
   case 0x3E:
   case 0x3F:
     if (cc->i.csi.state != CSI_STATE_INITIAL)
     break;
     cc->i.csi.isprivate = Code;
     cc->i.csi.state = CSI_STATE_PARAMETER;
     return;
   case 0x20:
   case 0x21:
   case 0x22:
   case 0x23:
 case 0x24:
   case 0x25:
   case 0x26:
   case 0x27:
   case 0x28:
   case 0x29:
   case 0x2A:
   case 0x2B:
   case 0x2C:
   case 0x2D:
   case 0x2E:
   case 0x2F:


     cc->i.csi.state = CSI_STATE_INTERMEDIATE;
     if (cc->i.csi.count == NumberOf(cc->i.csi.intermediate))
     break;
     cc->i.csi.intermediate[cc->i.csi.count++] = Code;
     return;
   default:


     cc->i.csi.current += 1;
     (*cc->call_CSI)(cc->client_data,
		     cc->i.csi.isprivate,
		     cc->i.csi.parameter,
		     cc->i.csi.current,
		     cc->i.csi.intermediate,
		     cc->i.csi.count,
		     Code);
     break;
   }
  ExitControl(cc);
}
