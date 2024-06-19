create or replace procedure crear_trig_suma(NombreEmpresa empresa.nombree%type) as
    plsql_block VARCHAR2(10000);
    nombreMayus VARCHAR2(100) := UPPER(nombreEmpresa);
    nombreLimpio VARCHAR2(200) := REPLACE(nombreMayus, ' ', '');
    nombreTrigger VARCHAR2(1000) := 'TRIG_SUMA_' || nombreLimpio;
    trigExiste NUMBER;
begin
    
    select count(*) into trigExiste
    from user_triggers
    where trigger_name = nombreTrigger;
    
    if trigExiste <> 0 then return;
    end if;

    plsql_block := 'CREATE OR REPLACE TRIGGER ' || nombreTrigger || ' AFTER INSERT ON INVERSIONES_' || nombreLimpio ||
                   ' FOR EACH ROW 
                     DECLARE 
                     estaEnSumaEmpresa NUMBER; 
                     BEGIN 
                     SELECT COUNT(*) INTO estaEnSumaEmpresa FROM SumaEmpresa WHERE NombreE = ''' || nombreEmpresa || ''';
                     IF estaEnSumaEmpresa = 0 THEN 
                     INSERT INTO SumaEmpresa VALUES ( ''' || nombreEmpresa || ''', :NEW.CANTIDAD); 
                     DBMS_OUTPUT.PUT_LINE( ''' || nombreEmpresa || ' insertada en la tabla SumaEmpresa ''' || ' ); 
                     ELSE 
                     UPDATE SumaEmpresa SET CANTIDAD = CANTIDAD + :NEW.CANTIDAD WHERE NOMBREE = ' || ''' || nombreEmpresa || ''' || ';
                     DBMS_OUTPUT.PUT_LINE( ''' || nombreEmpresa || ' actualizada en la tabla SumaEmpresa ''' || '); 
                     END IF; 
                     END; ';
    
    EXECUTE IMMEDIATE plsql_block;
    
end crear_trig_suma;