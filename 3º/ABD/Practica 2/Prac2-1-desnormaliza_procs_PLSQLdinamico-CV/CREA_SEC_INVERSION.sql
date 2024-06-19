create or replace PROCEDURE crea_sec_inversion(nombreEmpresa Invierte.NombreE%TYPE) 
AS
    si_esta_sec NUMBER;
    nombreSinEspacios VARCHAR2(20) := REPLACE(nombreEmpresa, ' ' , '');
    nombreSec VARCHAR2(50) := RTRIM(UPPER('sec_' || nombreSinEspacios));
    secuencia VARCHAR2(100) := 'CREATE SEQUENCE ' || nombreSec || ' START WITH 1 INCREMENT BY 1 MINVALUE 1';

BEGIN

    SELECT COUNT(object_name) INTO si_esta_sec 
    from user_objects
    where object_type = 'SEQUENCE' and object_name = nombreSec;
    
    dbms_output.put_line('Total: ' || si_esta_sec);
    
    -- Si la secuencia no existe, se crea con 'execute immediate'
    IF si_esta_sec = 0 THEN
        dbms_output.put_line('La secuencia no existe');
        EXECUTE IMMEDIATE secuencia;
        dbms_output.put_line('La secuencia ' || nombreSec || ' ha sido create con exito');
    ELSE -- Si la secuencia ya existe, se informa al usuario
        dbms_output.put_line('La secuencia ' || nombreSec || ' ya estaba creada');
    END IF;

END crea_sec_inversion;