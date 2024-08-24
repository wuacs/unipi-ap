import Ex1 (myReplicateR, myReplicateC)

replR :: [a] -> Int -> [[a]]
replR [] _ = []
replR (x:xs) n = (myReplicateC n x) : replR xs n

replC xs n = map (\x -> myReplicateC n x) xs 

main :: IO ()
main = do
    let resultRecursive = replR ["a", "b"] 3
    print resultRecursive
    let resultCombinator = replC ["a", "b"] 3
    print resultCombinator


