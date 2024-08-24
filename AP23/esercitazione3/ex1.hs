-- File: ex1.hs
module Ex1 (myReplicateR, myReplicateC) where

myReplicateR :: (Ord n, Num n) => n -> v -> [v] 
myReplicateR n _ 
            | n <= 0 = []
myReplicateR n v = v : myReplicateR (n-1) v


myReplicateC n v = map (\t -> v) [1..n]
