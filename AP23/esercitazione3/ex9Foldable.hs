-- IntTree implemented as an alias of a generic datatype for which we define foldable
-- sumSucc implemented thus using a combinator

data Tree a = Leaf a | Node (a, Tree a, Tree a)

instance Foldable Tree where
    foldr f z (Leaf x)   = (f x z)
    foldr f z (Node(v, l, r)) = (f v (foldr f (foldr f z l) r))

type IntTree = Tree Int

sumSucc :: IntTree -> Int

sumSucc tree = foldr (\x acc -> (succ x) + acc ) 0 tree 
