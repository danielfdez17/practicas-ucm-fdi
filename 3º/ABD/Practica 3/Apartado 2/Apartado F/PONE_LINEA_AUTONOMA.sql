create or replace PROCEDURE pone_linea_autonoma (milinea IN varchar)
  as
;
 
--- en proc que llama tiene: milinea varchar(100) :=  ' ';
 
 -- Hacemos transacci�n aut�noma 
 PRAGMA AUTONOMOUS_TRANSACTION;
 
BEGIN 

SET TRANSACTION ISOLATION LEVEL READ COMMITTED 
    NAME 'Linea_Autonoma';


DBMS_OUTPUT.PUT_LINE(milinea || ' Num.Trans.Secun: ' ||
                       dbms_transaction.local_transaction_id);

commit;  -- termina transacci�n, es obligatorio


end pone_linea_autonoma;

