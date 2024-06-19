/* 
  NO CREA EL TRIGGER; SOLO imprime el texto que genera, para comprobar que es eso
   lo que quieres.
   PARA crearlo, tienes que ejecutar el bloque: EXECUTE INMEDIATE trigger_block;

  -ANTES- RECORDAR EJECUTAR : SET AUTOCOMMIT ON   y   SET SERVEROUTPUT ON SIZE 100000

*/

declare
 
 nombreEsinBlancos VARCHAR2(40) := REPLACE('nombre Empresa', ' ', '');

    trigger_block VARCHAR2(2000) :=
 	'CREATE trigger trig_suma_' || nombreEsinBlancos || '
       after insert on inversiones_' || nombreEsinBlancos || '
       for each row
        declare 
            existeE INT;
	    nuevaCant INT := :new.cantidad;
        begin
           SELECT COUNT(*) INTO existeE 
             FROM SumaEmpresa S
             WHERE S.nombreE = ''' || nombreEsinBlancos ||  ''' ;           
       if existeE_sumaE = 0 then
             insert into SumaEmpresa values( ''' || nombreEsinBlancos  || ''' , nuevaCant);     
       else 
            UPDATE SumaEmpresa set cantidad =  cantidad + nuevaCant where nombreE = '''
                        || nombreEsinBlancos || ''';
       end if;   
   end;' ;

 
begin 
  DBMS_OUTPUT.PUT_LINE('que sale  trigger_block : ' ||  trigger_block);
end;
