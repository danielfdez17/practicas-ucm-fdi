create or replace PROCEDURE AUTOREGALACOMISIONES(
    DNICliente notificaciones.dni_cli%type,
    NombreE notificaciones.nombree%type,
    Tipo notificaciones.tipo%type,
    Cantidad invierte.cantidad%type) AS 
    
    tablespaceName varchar2(100);
    bytesLibres number;
    bloquesLibres number;
    
BEGIN
    -- insertar en la tabla ABD1003.Notificaciones una nueva fila en caso de que tengamos
    -- menos de 1800 bloques de espacio libre en nuestro tablespace
    for fila in (select tablespace_name, sum(blocks) as bloquesLibres
    from sys.dba_free_space
    where tablespace_name = 'ESPABD1003'
    --where rtrim(upper(replace(tablespace_name, ' ', ''))) = 'ABD1003.NOTIFICACIONES'
    group by tablespace_name
    order by bloquesLibres) loop
        if fila.bloquesLibres < 1800 then
    
                insert INTO ABD1003.notificaciones VALUES(
                    'ABDMITUIL', 
                    systimestamp, 
                    DNICliente, 
                    NombreE, 
                    Tipo, 
                    Cantidad * 0.02);
        
        end if;
    end loop;
    
END AUTOREGALACOMISIONES;