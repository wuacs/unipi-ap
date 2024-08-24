filterOddR :: [a] -> [a]

filterOddR [] = []
filterOddR (x:[]) = []
filterOddR (x:y:[]) = [y]
filterOddR (x:y:left) = y:filterOddR(left) 

filterOddC :: [a] -> [a]

filterOddC xs = snd (foldl (\ acc x -> if ((fst(acc) `mod` 2)==0) then (fst(acc)+1, snd (acc) ++ [x]) else (fst acc +1, snd acc)) (1, []) xs)