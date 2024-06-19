CREATE OR REPLACE TRIGGER TRIG_SUMA_PRUEBA 
BEFORE INSERT ON INVERSIONES_EMPRESA22 
FOR EACH ROW
DECLARE
    estaEnSumaEmpresa NUMBER;
BEGIN
    SELECT COUNT(*) INTO estaEnSumaEmpresa
    FROM SumaEmpresa
    WHERE NombreE = 'Empresa 22';
    
    IF estaEnSumaEmpresa = 0 THEN
        INSERT INTO SumaEmpresa VALUES ('Empresa 22', :NEW.CANTIDAD);
        DBMS_OUTPUT.PUT_LINE('Empresa 22 insertada en la tabla SumaEmpresa');
    ELSE
        UPDATE SumaEmpresa SET CANTIDAD = CANTIDAD + :NEW.CANTIDAD
        WHERE NOMBREE = 'Empresa 22';
        DBMS_OUTPUT.PUT_LINE('Empresa 22 actualizada en la tabla SumaEmpresa');
    END IF;

END;