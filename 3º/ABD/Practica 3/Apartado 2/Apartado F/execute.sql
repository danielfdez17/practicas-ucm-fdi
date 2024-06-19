set serveroutput on
set autocommit off
                       
SET TRANSACTION ISOLATION LEVEL READ COMMITTED 
    NAME 'TuTro';

SELECT dbms_transaction.local_transaction_id -- saber si estoy en una Trans.
 FROM dual ; 

-------- solo cuando queramos empezar en cero
                                    
drop sequence  sec_trans_1;

CREATE SEQUENCE sec_trans_1
 START WITH 0 INCREMENT BY 1 minvalue 0 MAXVALUE 1 CYCLE NOCACHE;

commit;


 

