CREATE OR REPLACE TRIGGER tr_anterior
AFTER INSERT ON INVIERTE
FOR EACH ROW 
BEGIN
   dbms_output.put_line('HOLA SOY EL TRIGGER ANTERIOR');
END;

create or replace trigger tr_anterior
after insert on invierte
for each row
begin
   dbms_output.put_line('Soy el trigger anterior');
end;