create or replace PROCEDURE trabajando_T1(X NUMBER) AS
    val_antes number;
    val_despues number;

BEGIN
    SELECT sec_T1.NEXTVAL INTO val_antes FROM dual;
    LOOP
        -- Llama al procedimiento para dormir durante X segundos
        ABDMIUTIL.dormir(X);
        
        SELECT sec_T1.NEXTVAL INTO val_despues FROM dual;
        
        -- Comprueba si debe terminar el bucle
        if val_antes = val_despues then
            dbms_output.put_line('La transaccion 1 ha terminado de trabajar');
            exit;
        end if;
        
        val_antes := val_despues;
  END LOOP;
  
  -- Muestra el mensaje de finalización junto con el número de transacción
  DBMS_OUTPUT.PUT_LINE('He terminado de trabajar. Transacción: ' || TO_CHAR(SYS.DBMS_TRANSACTION.LOCAL_TRANSACTION_ID));
END trabajando_T1;