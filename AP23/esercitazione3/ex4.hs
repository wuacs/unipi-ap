totalLengthR :: [[Char]] -> Int

length' :: [Char] -> Int
length' [] = 0
length' (x':xs') = if (x'=='A') then length(xs')+1 else 0

totalLengthR [] = 0
totalLengthR (x:xs) = length'(x) + totalLengthR(xs)

totalLengthC :: [[Char]] -> Int

totalLengthC xs = foldl (\ acc (x:xs') -> if (x=='A') then acc+(foldl (\acc' x' -> acc'+1) 0 xs') + 1 else acc) 0 xs