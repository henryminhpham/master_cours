-- MABD TP1 Prise en main de PL/SQL

-- -------------------- binome -------------------------
-- NOM
-- Prenom

-- NOM
-- Prenom
-- -----------------------------------------------------

-- procedure S1
-- affiche le code source d'une m�thode de l'utilisateur

create or replace procedure s1(nom in varchar2) is


-- cursor c is 


begin
   DBMS_OUTPUT.ENABLE (100000);


   dbms_output.put_line('code source de la m�thode ' || nom || ' : '); 

end;

/
show err
 



-- ex�cuter s1, pour afficher par exemple le code source de la procedure L1
begin
  s1('L1');
end;
/
