module AdventOfCode where

import System.Environment

addChar :: String -> Char -> String
addChar x y = x ++ [y]

splitStr :: String -> [String]
splitStr x = splitStrAux x ""
  where
    splitStrAux :: String -> String -> [String]
    splitStrAux "" _ = []
    splitStrAux (x : xs) y
      | x == '\n' = y : splitStrAux xs ""
      | otherwise = splitStrAux xs (addChar y x)

toNum :: [String] -> [Integer]
toNum = map (\x -> read x :: Integer)

difList :: [Integer] -> Integer -> [Integer]
difList [] _ = []
difList (x : xs) y = (y - x) : difList xs y

hasVal :: [Integer] -> Integer -> Integer
hasVal [] _ = -1
hasVal (x : xs) y
  | x == y = 2020 - x
  | otherwise = hasVal xs y

getPair :: [Integer] -> [Integer] -> (Integer, Integer)
getPair [] dif = (0, 0)
getPair (x : xs) dif
  | has /= -1 = (x, has)
  | otherwise = getPair xs dif
  where
    has = hasVal dif x

multPair :: (Integer, Integer) -> Integer
multPair (x, y) = x * y

main = do
  s <- readFile "input.txt"
  let inp = toNum (splitStr s)
  print (multPair (getPair inp (difList inp 2020)))