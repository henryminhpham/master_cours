-- creation des relations de l'exercice 3

drop table J;

create table J(licence number(10), 
  cnum number(10), 
  salaire number(10), 
  sport varchar(20)
);

drop table C;

create table C(  
  cnum number(10), 
  nom varchar(20),
  division number(1), 
  ville varchar(20)
);


drop table F;

create table F(  
  cnum number(10), 
  budget number(10),
  depense number(10),
  recette number(10)
);





-- definition de la procedure 
-- pour ajouter des tuples dans J,C et F

create or replace procedure ajouterJCF is
 n_salaire integer;
 n_club integer;
 n_sport integer;
 n_division integer;

begin

 DBMS_RANDOM.INITIALIZE(123456);

 FOR i in 1 .. 50000 LOOP

   n_club := abs(DBMS_RANDOM.RANDOM) mod 5000;
   n_salaire := abs(DBMS_RANDOM.RANDOM) mod 50000;
   n_sport := abs(DBMS_RANDOM.RANDOM) mod 200;

   insert into J values(i, n_club + 1, n_salaire + 10000, 'sport' || n_sport);

 END LOOP;

 FOR i in 1 .. 5000 LOOP

   n_division := abs(DBMS_RANDOM.RANDOM) mod 2;
   
   insert into C values( i, 'nom' ||i, n_division + 1, 'ville');
   insert into F values( i, 1000, 10, 100);

 END LOOP;

 DBMS_RANDOM.TERMINATE;
 commit;
end;
/

sho err


-- remplir les relations:
begin
 ajouterJCF();
end;
/
