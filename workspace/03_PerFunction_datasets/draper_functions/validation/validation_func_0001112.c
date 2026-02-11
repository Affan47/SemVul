deleteDescriptor(VimosDescriptor *vDesc)
{

  if (vDesc != NULL) {
      pil_free(vDesc->descName);
      pil_free(vDesc->descComment);

      switch (vDesc->descType) {
      case VM_STRING:
      case VM_INT_ARRAY:
      case VM_FLOAT_ARRAY:
      case VM_DOUBLE_ARRAY:
          if (vDesc->descValue->s) {
              pil_free(vDesc->descValue->s);
          }
          break;

      default:
          break;
      }
      deleteDescValue(vDesc->descValue);

      pil_free(vDesc);
  }

  return;

}
