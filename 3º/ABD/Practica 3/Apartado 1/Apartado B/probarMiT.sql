create or replace PROCEDURE probarMiT1 AS
BEGIN
  -- Empezar una transacción
  savepoint inicio_transaccion;
  -- Insertar tres compras y mostrar las filas insertadas
  INSERT INTO Compras VALUES ('11111111', 1, 1, TO_NUMBER(TO_CHAR(SYSDATE, 'YYYYMMDD')), 'Tienda1', 100);
  INSERT INTO Compras VALUES ('22222222', 2, 1, TO_NUMBER(TO_CHAR(SYSDATE, 'YYYYMMDD')) + 1, 'Tienda2', 150);
  INSERT INTO Compras VALUES ('33333333', 3, 1, TO_NUMBER(TO_CHAR(SYSDATE, 'YYYYMMDD')) + 2, 'Tienda3', 200);
  
  DBMS_OUTPUT.PUT_LINE('Filas insertadas para iniciar la transacción:');
  FOR rec IN (SELECT * FROM COMPRAS) LOOP
    DBMS_OUTPUT.PUT_LINE(rec.DNI || ', ' || rec.NUMT || ', ' || rec.NUMF || ', ' || rec.FECHA || ', ' || rec.TIENDA || ', ' || rec.IMPORTE);
  END LOOP;
  
  -- Parar la transacción llamando al procedimiento trabajando_T1
  trabajando_T1(5);

  -- Insertar otras tres compras y mostrar las filas insertadas
  INSERT INTO Compras (DNI, NumT, NumF, Fecha, Tienda, Importe)
  VALUES ('44444444', 4, 1, 20240307, 'Tienda4', 120);
  INSERT INTO Compras (DNI, NumT, NumF, Fecha, Tienda, Importe)
  VALUES ('55555555', 5, 1, 20240307, 'Tienda5', 180);
  INSERT INTO Compras (DNI, NumT, NumF, Fecha, Tienda, Importe)
  VALUES ('66666666', 6, 1, 20240307, 'Tienda6', 220);
  COMMIT;
  DBMS_OUTPUT.PUT_LINE('Filas insertadas después de parar la transacción:');

  -- Parar la transacción nuevamente llamando al procedimiento trabajando_T1
  trabajando_T1(5);
  
  INSERT INTO Compras VALUES ('11111111', 1, 1, TO_NUMBER(TO_CHAR(SYSDATE, 'YYYYMMDD')) + 3, 'Tienda1', 100);
  INSERT INTO Compras VALUES ('22222222', 2, 1, TO_NUMBER(TO_CHAR(SYSDATE, 'YYYYMMDD')) + 4, 'Tienda2', 150);
  INSERT INTO Compras VALUES ('33333333', 3, 1, TO_NUMBER(TO_CHAR(SYSDATE, 'YYYYMMDD')) + 5, 'Tienda3', 200);

  DBMS_OUTPUT.PUT_LINE('Filas insertadas para parar la transacción:');
  FOR rec IN (SELECT * FROM COMPRAS) LOOP
    DBMS_OUTPUT.PUT_LINE(rec.DNI || ', ' || rec.NUMT || ', ' || rec.NUMF || ', ' || rec.FECHA || ', ' || rec.TIENDA || ', ' || rec.IMPORTE);
  END LOOP;

  -- Parar la transacción nuevamente llamando al procedimiento trabajando_T1
  trabajando_T1(5);

  -- Si llega aquí, la transacción ha terminado
  DBMS_OUTPUT.PUT_LINE('La transacción ha terminado.');
EXCEPTION
  WHEN OTHERS THEN
    ROLLBACK TO inicio_transaccion;
    DBMS_OUTPUT.PUT_LINE('Error: ' || SQLERRM);
END probarMiT1;