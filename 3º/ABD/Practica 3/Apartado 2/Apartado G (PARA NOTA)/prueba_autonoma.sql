create or replace procedure prueba_autonoma as
begin
  insert into invierte values ('00000003', 'EMPRESA11', 10000, 'bono1', 'BlackFri');
    dbms_output.put_line('Transaccion previa al commit: ' || dbms_transaction.local_transaction_id);
  ROLLBACK;
  dbms_output.put_line('Transaction despues del rollback: ' || dbms_transaction.local_transaction_id);

  for row in (select * from invierte)
  loop
    dbms_output.put_line('DNI: ' || row.dni ||
                         'NombreEmpresa: ' || row.nombree ||
                         'Cantidad: ' || row.cantidad ||
                         'Tipo: ' || row.tipo
    );
  end loop;
end prueba_autonoma;


