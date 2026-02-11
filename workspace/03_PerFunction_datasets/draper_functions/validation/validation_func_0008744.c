triggerGenericHook( const uint32_t & id, const uint32_t & n,
                            void * a0, void * a1, void * a2, void * a3,
                            void * a4, void * a5, void * a6, void * a7,
                            void * a8, void * a9, void * a10, void * a11,
                            void * a12, void * a13 )
{
   if( m_hooks.empty() ) return;


   VaArgsT args =
      { a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13 };


   for( uint32_t i = 0; i < m_hooks.size(); i++ )
      m_hooks[i]->genericHook( id, args );
}
