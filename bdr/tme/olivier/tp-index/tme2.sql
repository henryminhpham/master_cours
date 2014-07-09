-- Compléter l'entête de ce fichier:

-- Pitton Oliver:
-- Metin Hakan :
-- NumÃ©ro de Binome:

-- Compte rendu du TME sur les index : complÃ©ter ce fichier
-- ==================================


-- PrÃ©paration :
-- crÃ©ation de la relation Annuaire
-- @annuaire


-- 2) Proposer une requete pour vÃ©rifier que la distribution de l'attribut 
--    age est uniforme.

select age, count(age) 
from annuaire 
group by age 
order by age;

-- Nous montre que la distribution de la table est quasiment uniforme


-- 3) Proposer une requete pour vÃ©rifier que les attributs age et prÃ©nom 
--    sont indÃ©pendants.

select age, count(distinct prenom) 
from annuaire 
group by age 
d  | Operation	  | Name     | Rows  | Bytes | Cost (%CPU)| Time     |
------------------------------------------------------------------------------
|   0 | SELECT STATEMENT  |	     |	6465 |	 176K|	  14   (0)| 00:00:01 |
|*  1 |  TABLE ACCESS FULL| ANNUAIRE |	6465 |	 176K|	  14   (0)| 00:00:01 |
------------------------------------------------------------------------------
d  | Operation	  | Name     | Rows  | Bytes | Cost (%CPU)| Time     |
------------------------------------------------------------------------------
|   0 | SELECT STATEMENT  |	     |	6465 |	 176K|	  14   (0)| 00:00:01 |
|*  1 |  TABLE ACCESS FULL| ANNUAIRE |	6465 |	 176K|	  14   (0)| 00:00:01 |
------------------------------------------------------------------------------
order by age;

-- permet de verifier pour un certain age le nombre de prenom distinct
-- select count(distinct prenom) from annuaire;
-- permet d obtenier le nombre total de prenom distinct

select prenom, count(distinct age) from annuaire group by prenom order by prenom;
permet de verifier pour un certain prenom le nombre de age distinct
select count(distinct age) from annuaire;
permet d obtenier le nombre total d age distinct

On voit bien qu il n y a pas tous les prenoms possible pour un certain age.
 Il n y a pas tous les ages possible pour un certain prenom.

-- 4) calculer puis vÃ©rifier la cardinalitÃ© des requetes suivantes:
-- ===============================================================

-- R1: select * from Annuaire; #(R1) = 10000
-- R2: select * from Annuaire where age < 65; #(R2) = 10000*65/100 =estimé 6500, résultat 6439
-- R3: select * from Annuaire where cp between 75000 and 78000; #(R3) = estimé 303.03, résultat 324 
-- R4: select * from Annuaire where age=18 and cp < 1200; #(R4) = estimé 0.2, résultat 1
-- R5: select * from Annuaire where age=18 and cp = 1200; #(R5) = estimé 0.1, résultat 0
-- R6: select count(*) from Annuaire where age < 65; #(R6) = 1



-- 5)
create index iage on annuaire(age);
create index icp on annuaire(cp);

alter session set optimizer_mode = rule;

-- 5.1) Pour chaque requete, afficher les index utilisÃ©s par le moteur de requete. 

	R1  ---

	R2  INDEX RANGE SCAN    | IAGE 

	R3  INDEX RANGE SCAN    | ICP 

	R4 1 |  TABLE ACCESS BY INDEX ROWID | ANNUAIRE |
	   2 |   INDEX RANGE SCAN	    | IAGE

	R5 1 |  TABLE ACCESS BY INDEX ROWID| ANNUAIRE |
	   2 |   AND-EQUAL		    |	       |
	   3 |    INDEX RANGE SCAN	    | IAGE     |
	   4 |    INDEX RANGE SCAN	    | ICP

	R6 1 |  SORT AGGREGATE   |	 |
	   2 |   INDEX RANGE SCAN| IAGE


-- En dÃ©duire les rÃ¨gles heuristiques que l'optimiseur utilise pour choisir un index.
l optimiseur utilise la taille de l espace des attributs comme heuristique si il existe un index sur les
attributs.
S'il y a une égalité et une inégalité, Oracle choisit en premier lieu l'égalité s'il y a un index. 

-- @config_autotrace 
-- set autotrace trace explain stat
-- pour dÃ©sactiver ce mode : set autotrace off

-- 5.2)

SELECT * FROM annuaire WHERE age < 200 AND cp > 10; 
Cette requête provoque 9871 consistent gets alors qu'elle est équivalente à un SELECT * FROM Annuaire. Cette-dernière ne provoque en revanche que 728 consistent gets. L'optimiseur n'est pas capable de déterminer que ces requêtes sont équivalentes.

-- 6.1)

LOW_VALUE = Valeur la plus faible
HIGH_VALUE = Valeur la plus élevée
NUM_ROWS = Nombre de lignes
NUM_DISTINCT = Nombre de lignes distinctes.
BLOCKS = Nombre de blocs pris
INDEX_TYPE = Le type d'index utilisé

-- 6.2)

R1 : Aucun index n'est utilisé
R2 : Aucun index n'est utilisé 
R3 : Aucun index n'est utilisé
R4 : Oracle utilise 2 index pour traiter la requête et fait une jointure sur les résultats produits. Cette jointure est effectuée directement avec les row id. L'optimiseur se base sur la sélectivité pour le modèle de coût, ce qui implique qu'il décide d'utiliser un index s'il juge que son utilisation sera meilleure que de parcourir directement les row id, après une projection. Ici, puisque le nombre de valeurs de l'inégalité est très petites, puisque proche de la valeur minimale, il décide d'utiliser un index pour récupérer celles-ci, et faire une jointure après.
R5 : Identique à la requête précédente pour les mêmes raisons

-- 6.2.1°)

Oracle utilise le modèle par cout pour choisir les index à utiliser. S'il considère que le gain apporté par l'index n'est pas optimal  face à la pure exécution de la requête, il utilise la requête sans index.

-- 6.2.2°) 

Non. Effectuer avec précision le plan d'exécution pourrait prendre plus de temps que d'effectuer purement et simplement la requête. Le gain apporté par la génération de plan d'exécution optimisé peut être null si le temps perdu par une requête moins optimisée est compensée par une génération de plan d'exécution optimisée. Générer un meilleur plan n'est pas un réel bénéfice si le temps pour le générer est supérieur au gain qu'il apporte. Donc un plan extrêmement optimisé, impliquant des plans moins optimisés, peut ne pas être si bénéfique.

-- 6.3°)

La sélectivité est de 1 / 1000. Oracle utilise l'index sur cp à partir du moment où cp vaut "1130".

La sélectivité est de 1 / 1000. Oracle utilise l'index sur cp à partir du moment où cp vaut "1130" et l'index sur age à partir du moment où age vaut 3.
