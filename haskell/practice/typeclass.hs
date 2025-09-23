class Tofu t where  
    tofu :: j a -> t a j
-- j=a(*)->type(*)
-- j:(*->*)
-- t=a->j->type
-- t=*->(*->*)->*
-- {k} (t :: k -> (k -> *) -> *) (j :: k -> *) (a :: k).

data Frank a b  = Frank {frankField :: b a} deriving (Show)
-- * -> ( *->* ) ->*
-- 实际上部分应该是k，他是concrete类不是更抽象的kind
-- k -> (k -> *) -> *

instance Tofu Frank where  
    tofu x = Frank x