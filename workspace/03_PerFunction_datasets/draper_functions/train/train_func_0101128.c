set_allow_user_actions(bool bVal)
{
  AddDel::set_allow_user_actions(bVal);


  if(bVal)
  {
    set_allow_user_actions(false);


    setup_buttons();
  }
  else
  {

    m_ButtonBox.remove(m_Button_Add);
    m_ButtonBox.remove(m_Button_Del);
    m_ButtonBox.remove(m_Button_Edit);
  }


  setup_menu();
}
