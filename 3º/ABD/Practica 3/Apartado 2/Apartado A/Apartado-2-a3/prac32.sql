CREATE OR REPLACE TRIGGER PRAC32 
AFTER INSERT ON INVIERTE 
FOR EACH ROW
BEGIN
    -- este trigger llama al procedimiento autoRegalaComisiones
    autoRegalaComisiones(:new.dni, :new.nombree, :new.tipo, :new.cantidad);
END;