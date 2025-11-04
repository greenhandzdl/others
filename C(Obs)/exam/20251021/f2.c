typedef struct TreeNode *Tree;
struct TreeNode
{
   int Key;
   Tree  Left;
   Tree  Right;
};

void Level_order ( Tree T )
{
   Queue Q;

   if ( !T ) return; 
   Q = CreateQueue( MaxElements ); 
   Enqueue( T, Q ); 
   while ( !IsEmpty( Q ) ){
      T = Front_Dequeue ( Q ); /* return the front element and delete it from Q */
      printf("%d ", T->Key);
      if ( T->Left ) 
         Engage( T->Left, Q );
      if ( T->Right ) 
         Engage( T->Right, Q );
   }
}