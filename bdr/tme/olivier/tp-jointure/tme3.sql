-- NOM: 
-- Prénom: 

-- NOM: 
-- Prénom: 

-- Binome: 

-- ==========================

-- TME3:

-- Préparation
-- ===========

-- construire la base de l'exercice 3
-- @base3
-- @index3

-- activer la visualisation des plans d'exécution
set autotrace trace explain stat


-- la requete R
-- =============
select /*+ use_nl(c,j,f) */ c.nom, f.budget 
from C, J, F
where J.cnum = C.cnum and C.cnum = F.cnum
and c.division=1 and J.salaire > 59000  
and j.sport = 'sport1';




-- utiliser les directives d'optimisation (hint) suivantes : 
-- ordered : fixe l'ordre de traitement des jointures : 
--           l'ordre imposé est celui indiqué dans la clause 'FROM' de la requete.
-- index(nom_relation nom_index) : pour forcer un acces par index
-- no_index(nom_relation nom_index) : pour interdire l'utilisation d'un index


-- exemple: le plan P1 avec l'ordre (J |><| C)  |><| F

select /*+ use_nl(c,j,f) ordered */  c.nom, f.budget 
from J, C, F
where J.cnum = C.cnum and C.cnum = F.cnum
and c.division=1 and J.salaire > 59000  
and j.sport = 'sport1';

