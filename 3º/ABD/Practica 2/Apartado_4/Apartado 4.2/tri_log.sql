CREATE OR REPLACE TRIGGER TRI_LOG 
AFTER INSERT OR UPDATE ON SUMAEMPRESA 
FOR EACH ROW
DECLARE 
    currentTime timestamp;
    operation VARCHAR2(20);
BEGIN
    select systimestamp into currentTime from dual;
    if inserting then
        operation := 'INSERT';
    else
        operation := 'UPDATE';
    end if;
    insert into LOGSUMAS values (
            currentTime,
            operation,
            :NEW.CANTIDAD,
            :NEW.NOMBREE);
    if :new.cantidad > 100000000 then
        raise_application_error(-20999, 'Cantidad superior a 100.000.000 de euros');
    end if;
  NULL;
END;