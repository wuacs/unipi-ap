data IntTree = Leaf Int | Node (Int, IntTree, IntTree)

tmap :: IntTree -> (Int -> Int) -> IntTree

tmap (Leaf t) f = (Leaf (f t))
tmap (Node(n, it1, it2)) f = Node((f n), (tmap it1 f), (tmap it2 f))

succTree :: IntTree -> IntTree

succTree x = tmap x succ

sumSucc :: IntTree -> Int

sumSucc (Leaf l) = succ(l)
sumSucc (Node (n, it1, it2)) = succ(n) + sumSucc(it1) + sumSucc(it2) 

showall :: IntTree -> String

showall (Leaf t) =  show t
showall (Node(n, it1, it2)) = show n ++ "," ++ showall(it1) ++ "," ++ showall(it2)