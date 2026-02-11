pack_basis(basis_desc *basis, char explicit_packing)
{
   send_char_array(&basis->basis_exists, 1);
   if (basis->basis_exists){
      pack_double_array_desc(&basis->baserows, explicit_packing);
      pack_double_array_desc(&basis->extrarows, explicit_packing);
      pack_double_array_desc(&basis->basevars, explicit_packing);
      pack_double_array_desc(&basis->extravars, explicit_packing);
   }
}
