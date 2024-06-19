create or replace PROCEDURE CREAR_TRIGGERS AS 
    
    nombreTabla Empresa.nombreE%type;
    triggerExiste NUMBER;

BEGIN
    
    -- crear un trigger para cada tabla inversiones_xxxxxx con crear_trig_suma(nombreEmpresa)
    -- se itera sobre todas las tablas de inversiones
    for tabla in (select table_name
                  from tabs
                  where table_name like 'INVERSIONES_%')
    loop
        nombreTabla := substr(tabla.table_name, 13);
        -- se comprueba si el trigger esta creado y, en caso afirmativo, si esta habilitado
        select count(*) into triggerExiste
        from user_triggers
        where trigger_name = 'TRIG_SUMA_' || nombreTabla;
        
        if triggerExiste = 0 then
            crear_trig_suma(nombreTabla);
            dbms_output.put_line('Ahora la empresa ' || nombreTabla || ' tiene creado el trigger que actualiza la tabla SumaEmpresa');
        else
            execute immediate 'alter trigger TRIG_SUMA_' || upper(nombreTabla) || ' enable';
            dbms_output.put_line('La empresa ' || nombreTabla || ' ya tenia creado el trigger que actualiza la tabla SumaEmpresa');
        end if;
        
    end loop;
    -- antes de crear el trigger hay que coprobar si existe o no
END CREAR_TRIGGERS;