-- |
-- -- @Module : Cha5
-- -- @Brief : Module avec les fonctions nécéssaire pour créer le challenge 5.
-- -- @Date : 2023
-- -- @Description : Contient l'ensemble des contraintes pour l'épreuve 5.
module Cha5
  ( challenge5,
  )
where

import CPL

-- |
-- -- @Name : door1
-- -- @Brief : Condition de la porte 1
-- -- @Arguments : Rien
-- -- @Return : Retourne une formule
door1 :: Formula
door1 = Var "p1"

-- |
-- -- @Name : door2
-- -- @Brief : Condition de la porte 2
-- -- @Arguments : Rien
-- -- @Return : Retourne une formule
door2 :: Formula
door2 = Var "t1"

-- |
-- -- @Name : constraint1
-- -- @Brief : est une fonction générant une formule permettant de définir la contrainte 1  du challenge5
-- -- @Arguments : Aucun
-- -- @Return : Une formule
constraint1 :: Formula
constraint1 = Not (Eqv (And door2 door1) (And door2 (Not door1)))

-- |
-- -- @Name : constraint2
-- -- @Brief : est une fonction générant une formule permettant de définir la contrainte 2  du challenge5
-- -- @Arguments : Aucun
-- -- @Return : Une formule
constraint2 :: Formula
constraint2 = Not (Eqv (And door2 door1) (And door2 (Not door1)))

-- |
-- -- @Name --> challenge5
-- -- @Brief --> est une fonction générant le challenge 5
-- -- @Arguments --> Aucun
-- -- @Return --> Une formule
challenge5 :: Formula
challenge5 = And constraint1 constraint2