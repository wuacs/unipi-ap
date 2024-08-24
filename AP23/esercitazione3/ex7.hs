import Data.Char (toUpper)

countVowelPaliR :: [[Char]] -> Int

countVowelsHelperR :: [Char] -> Int

countVowelsHelperR [] = 0

countVowelsHelperR (x:xs) = (if (elem (toUpper x) ['A', 'E', 'I', 'O', 'U']) then 1 else 0) + countVowelsHelperR xs

countVowelPaliR [] = 0

countVowelPaliR (word:words) = (if ((reverse word) == word) then (countVowelsHelperR word) else 0) + (countVowelPaliR words)

countVowelPaliC :: [[Char]] -> Int

countVowelPaliC words = foldl (\ acc x -> if ((reverse x)==x) then
                        acc+(foldl (\ acc' x' -> if (elem (toUpper x') ['A', 'E', 'I', 'O', 'U']) then acc'+1 else acc') 0 x) else
                        acc) 0 words