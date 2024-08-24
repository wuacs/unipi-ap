-- map with foldl

map1 :: (a -> b) -> [a] -> [b]

map1 f xs = foldl (\acc x -> acc ++ [(f x)]) [] xs