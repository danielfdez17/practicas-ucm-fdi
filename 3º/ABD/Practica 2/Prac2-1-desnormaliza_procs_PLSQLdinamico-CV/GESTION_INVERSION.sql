create or replace PROCEDURE Gestion_Inversion(DNICliente Invierte.DNI%TYPE,
                                              NombreEmpresa Invierte.NombreE%TYPE,
                                              CantidadInversion Invierte.Cantidad%TYPE,
                                              TipoInversion Invierte.Tipo%TYPE,
                                              CodOfertaInv Invierte.CodOferta%TYPE)
AS
    empresaExiste NUMBER;
    nextNumInv NUMBER;
    consultaNextNumInv VARCHAR2(100) := 'SELECT SEC_' || nombreEmpresa || '.NEXTVAL FROM DUAL';
    insercion VARCHAR2(1000) := '';
BEGIN

    SELECT COUNT(*) INTO empresaExiste 
    FROM Empresa
    WHERE NombreE = NombreEmpresa;
    
    IF empresaExiste <> 0 THEN
        dbms_output.put_line('La empresa ' || nombreEmpresa || ' existe en la tabla Empresa');
        CREA_SEC_INVERSION(nombreEmpresa);
        CREA_TABLA_INVERSIONES(nombreEmpresa);
        EXECUTE IMMEDIATE consultaNextNumInv INTO nextNumInv;
        insercion := 'INSERT INTO TABLA_' || nombreEmpresa
                                || ' VALUES (' || DNICliente 
                                || ', ' || nextNumInv
                                || ', ' || CantidadInversion
                                || ', ' || TipoInversion
                                || ', ' || CodOfertaInv || ')';
        dbms_output.put_line('Fila insertada');
        dbms_output.put_line('DNI: ' || DNICliente);
        dbms_output.put_line('NumInv: ' || nextNumInv);
        dbms_output.put_line('Cantidad: ' || CantidadInversion);
        dbms_output.put_line('Tipo: ' || TipoInversion);
        dbms_output.put_line('CodOferta: ' || CodOfertaInv);

    ELSE 
        dbms_output.put_line('La empresa ' || nombreEmpresa || ' no existe en la tabla Empresa');
    END IF;
END Gestion_Inversion;