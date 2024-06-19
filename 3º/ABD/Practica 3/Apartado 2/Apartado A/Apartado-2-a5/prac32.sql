create or replace TRIGGER PRAC32 
AFTER INSERT ON INVIERTE 
FOR EACH ROW
BEGIN
    -- este trigger llama al procedimiento RegalaComisiones
    RegalaComisiones(:new.dni, :new.nombree, :new.tipo, :new.cantidad);
END;