-- |
-- -- @Module : Cha6
-- -- @Brief : Module avec les fonctions nécéssaire pour créer le challenge .
-- -- @Date : 2023
-- -- @Description : Contient l'ensemble des contraintes pour l'épreuve 6.
module Cha6
  ( challenge6,
  )
where

import CPL

-- |
-- -- @Name : door1
-- -- @Brief : Condition de la porte 1
-- -- @Arguments : Rien
-- -- @Return : Retourne une formule
door1 :: Formula
door1 = Var "t1"

-- |
-- -- @Name : door2
-- -- @Brief : Condition de la porte 2
-- -- @Arguments : Rien
-- -- @Return : Retourne une formule
door2 :: Formula
door2 = Var "p1"

-- |
-- -- @Name : door3
-- -- @Brief : Condition de la porte 3
-- -- @Arguments : Rien
-- -- @Return : Retourne une formule
door3 :: Formula
door3 = Var "t2"

-- |
-- -- @Name : constraint1
-- -- @Brief : est une fonction générant une formule permettant de définir la contrainte 1  du challenge 6
-- -- @Arguments : Aucun
-- -- @Return : Une formule
constraint1 :: Formula
constraint1 = And (And (Not door1) (Not door2)) (And (Not door2) door3)

-- |
-- -- @Name : constraint2
-- -- @Brief : est une fonction générant une formule permettant de définir la contrainte 2  du challenge 6
-- -- @Arguments : Aucun
-- -- @Return : Une formule
constraint2 :: Formula
constraint2 = And (And (Not door1) door2) (And door2 (Not door3))

-- |
-- -- @Name : constraint3
-- -- @Brief : est une fonction générant une formule permettant de définir la contrainte 2  du challenge 6
-- -- @Arguments : Aucun
-- -- @Return : Une formule
constraint3 :: Formula
constraint3 = And (And door1 (Not door2)) (And (Not door2) (Not door3))

-- |
-- -- @Name --> challenge6
-- -- @Brief --> est une fonction générant le challenge 6
-- -- @Arguments --> Aucun
-- -- @Return --> Une formule
challenge6 :: Formula
challenge6 = Or (Or constraint1 constraint2) (Or constraint2 constraint3)