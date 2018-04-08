 # i n c l u d e   " s t d a f x . h "  
 # i n c l u d e   < m p i . h >  
 # i n c l u d e   " s t d i o . h "  
 # i n c l u d e   " s t d l i b . h "  
 # i n c l u d e   " I n i t i a l i z e r . h "  
 # i n c l u d e   " C o l l e c t o r . h "  
 # i n c l u d e   " M u l t i p l i e r . h "  
  
  
 i n t   m u l t i p l i e r s [ ]   =   {   1 ,   2 ,   3 ,   4   } ;  
 i n t   m u l t i p l i e r s N u m   =   4 ;  
 i n t   i n i t i a l i z e r   =   0 ;  
 i n t   c o l l e c t o r   =   5 ;  
  
 b o o l   c h e c k I s M u l t i p l i e r ( i n t   r a n k ) ;  
  
 i n t   m a i n ( i n t   a r g c ,   c h a r   * a r g v [ ] )  
 {  
 	 i n t   r a n k ;  
  
 	 M P I _ I n i t ( & a r g c ,   & a r g v ) ;  
 	 M P I _ C o m m _ r a n k ( M P I _ C O M M _ W O R L D ,   & r a n k ) ;  
  
 	 i f   ( r a n k   = =   i n i t i a l i z e r )   {  
 	 	 i n i t i a l i z e ( m u l t i p l i e r s ,   4 ,   i n i t i a l i z e r ,   1 0 ) ;  
 	 }  
 	 e l s e   i f   ( c h e c k I s M u l t i p l i e r ( r a n k ) )   {  
 	 	 m u l t i p l i c a t o r ( 0 ,   r a n k ,   c o l l e c t o r ,   1 0 ) ;  
 	 }  
 	 e l s e   i f   ( r a n k   = =   c o l l e c t o r )  
 	 {  
 	 	 c o l l e c t ( m u l t i p l i e r s ,   4 ,   r a n k ,   1 0 ) ;  
 	 }  
  
 	 M P I _ F i n a l i z e ( ) ;  
  
         r e t u r n   0 ;  
 }  
  
 b o o l   c h e c k I s M u l t i p l i e r ( i n t   r a n k )   {  
 	 f o r   ( i n t   i ( 0 ) ;   i   <   m u l t i p l i e r s N u m ;   i + + )    
 	 	 i f   ( m u l t i p l i e r s [ i ]   = =   r a n k )  
 	 	 	 r e t u r n   t r u e ;  
 	  
 	 r e t u r n   f a l s e ;  
 } 
