#define leftchild(i) ( 2*(i)+1 )

void BuildMinHeap( ElementType A[], int N )
{  int i, j, child;
   ElementType Tmp;

   for ( i = (N-1)/2; i >= 0; i-- ) {
      j = i;
      for ( Tmp = A[j]; leftchild(j) < N; j = child ) {
         child = leftchild(j);
         if ( child != N-1 && A[child+1] < A[child] )
            child ++;
         if ( Tmp > A[child] )   A[j] = A[child];
         else  break;
      }
      A[j] = Tmp;
   }
}