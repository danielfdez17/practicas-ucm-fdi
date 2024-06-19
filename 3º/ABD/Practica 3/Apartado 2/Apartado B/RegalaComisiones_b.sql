create or replace PROCEDURE RegalaComisiones_b (
    DNICliente IN NOTIFICACIONES.DNI_CLI%TYPE,
    NombreE IN NOTIFICACIONES.NOMBREE%TYPE,
    Tipo IN NOTIFICACIONES.TIPO%TYPE,
    Cantidad invierte.cantidad%type
) AS 
    v_space_left NUMBER;
    v_table_exists NUMBER;
    v_total_sum number;
    v_schema_name VARCHAR2(30);
    pragma autonomous_transaction;
BEGIN
    -- Loop a través de todos los usuarios de la base de datos que tienen tablas en ABD
    FOR user_rec IN (SELECT DISTINCT OWNER FROM ALL_TABLES WHERE OWNER LIKE 'ABD%' AND TABLE_NAME LIKE '%NOTIFICACIONES') LOOP
        
        savepoint inicioBucle;        
        -- Obtener el nombre del esquema del usuario actual
        v_schema_name := user_rec.OWNER;

        -- Verificar si existe la tabla Notificaciones para el usuario actual
        SELECT COUNT(*) INTO v_table_exists FROM ALL_TABLES WHERE OWNER = v_schema_name AND TABLE_NAME = 'NOTIFICACIONES';

        -- Si la tabla existe para este usuario
        IF v_table_exists > 0 THEN
            -- Obtener el espacio libre en el tablespace del usuario actual
            SELECT SUM(blocks) INTO v_space_left FROM sys.dba_free_space WHERE tablespace_name = v_schema_name;

            -- Verificar si el usuario tiene menos de 1800 bloques de espacio libre
            IF v_space_left < 1800 THEN
                -- Construir la consulta de inserción dinámica
                EXECUTE IMMEDIATE 'INSERT INTO ' || v_schema_name || '.notificaciones (Usuario_Origen, Fecha, DNI_cli, NombreE, Tipo, Comision) ' ||
                                  'VALUES (''ABDMITUIL'', SYSTIMESTAMP, :DNICliente, :NombreE, :Tipo, ' || Cantidad * 0.02 || ')'
                USING DNICliente, NombreE, Tipo;
                
                execute immediate 'select sum(comision) from ' || v_schema_name || '.notificaciones' into v_total_sum;
                
                if v_total_sum >= 100 then
                    dbms_output.put_line('Se hace rollback de la iteracion porque se ha superado la suma de 100 en todas las comisiones (ID Transaction: ' || dbms_transaction.local_transaction_id);
                    rollback to inicioBucle;
                end if;
            END IF;
        END IF;
    END LOOP;
    
    dbms_output.put_line('ID Transaccion terminada con commit: ' || dbms_transaction.local_transaction_id);
    commit;
    exception
    when others then dbms_output.put_line('Error en el procedimiento RegalaComisiones_b');
    rollback;
END RegalaComisiones_b;