create or replace PROCEDURE Suma_inversiones(DNICliente Cliente.DNI%TYPE) AS
    
    inversionTotal NUMBER := 0;
    inversionEmpresa NUMBER := 0;

BEGIN

    FOR fila IN (SELECT table_name 
                 FROM TABS
                 WHERE UPPER(table_name) LIKE 'INVERSIONES_%') LOOP
             EXECUTE IMMEDIATE 'SELECT NVL(SUM(Cantidad), 0) '
                                || 'FROM ' || fila.table_name
                                || ' WHERE DNI = ' || DNICliente
                                || ' INTO ' || inversionEmpresa;
            dbms_output.put_line('Inversion en empresa ' || fila.table_name || ': ' || inversionEmpresa);
    END LOOP;
    dbms_output.put_line('El cliente con DNI ' || DNICliente || ' tiene una inversion total de ' || inversionTotal || ' euros');
END Suma_inversiones;