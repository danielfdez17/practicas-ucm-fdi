create or replace trigger prac32 
after insert on invierte
for each row 
follows tr_anterior 
begin
  regalacomisiones_d(:new.dni, :new.nombree, :new.cantidad, :new.tipo);
end;
