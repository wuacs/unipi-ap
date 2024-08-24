sumOddR :: [Integer] -> Integer
sumOddR [] = 0
sumOddR (int1:ints) = (if ((int1 `mod` 2)==0) then 0 else int1) + sumOddR(ints) 

sumOddC :: [Integer] -> Integer
sumOddC [] = 0
sumOddC (ints) = foldl (\ acc x -> if ((x `mod` 2)==0) then acc else x+acc) 0 ints