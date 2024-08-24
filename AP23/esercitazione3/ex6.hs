import Data.Char (toUpper)

titlecaseR :: String -> String
helperR :: [[Char]] -> [[Char]]

helperR [] = []
helperR ((s':ss'):ss) = (toUpper(s'):ss'):helperR(ss)
titlecaseR s = unwords(helperR(words(s)))

-- combinator version

titlecaseC :: String -> String

titlecaseC s = unwords((map (\ (x:xs) -> toUpper(x):xs) (words(s))))