CREATE OR REPLACE
PROCEDURE PRU_TRI_SUMA AS 
    nombreTabla Empresa.nombreE%type;
    nombreTrigger VARCHAR2(100);
    statusTrigger VARCHAR2(100);
BEGIN
    select status into statusTrigger
    from user_triggers
    where trigger_name = 'TRI_LOG';
    
    if statusTrigger = 'DISABLE' then
        execute immediate 'alter trigger TRI_LOG enable';
    end if;
    
    -- vaciar la tabla SumaEmpresa
    delete from SumaEmpresa;
    -- iterar sobre las tablas 'inversiones_xxxxxx' y vaciarlas
    for tabla in (select table_name
                  from tabs
                  where table_name like 'INVERSIONES_%')
    loop
        nombreTabla := substr(tabla.table_name, 13);
        execute immediate 'DELETE FROM INVERSIONES_' || nombreTabla;
    end loop;
    -- ejecuta partir_tabla_invierte
    partir_tabla_invierte();
    -- imprimir cada fila de la tabla SumaEmpresa
    for fila in (select *
                 from SumaEmpresa)
    loop
        dbms_output.put_line('Nombre de la empresa: ' || fila.nombree || '; Suma total: ' || fila.cantidad);
    end loop;
END PRU_TRI_SUMA;