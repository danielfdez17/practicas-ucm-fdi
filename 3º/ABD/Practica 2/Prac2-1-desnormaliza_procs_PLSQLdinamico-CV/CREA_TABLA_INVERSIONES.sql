create or replace procedure crea_tabla_inversiones(nombreEmpresa Invierte.NombreE%TYPE)
AS
    si_esta_tabla_creada NUMBER;
    nombreSinEspacios VARCHAR2(20) := REPLACE(nombreEmpresa, ' ' , '');
    nombreTabla VARCHAR2(50) := RTRIM(UPPER('tabla_' || nombreSinEspacios));
    tabla VARCHAR2(1000) := 'CREATE TABLE ' || UPPER(nombreTabla) || ' ('
                            || 'DNI CHAR(8) not null REFERENCES Cliente(DNI), '
                            || 'NumInv NUMBER PRIMARY KEY, '
                            || 'Cantidad FLOAT, '
                            || 'Tipo CHAR(10) not null, '
                            || 'CodOferta CHAR(8) REFERENCES Oferta(CodOferta)'
                            || ')';
BEGIN
    SELECT COUNT(table_name) INTO si_esta_tabla_creada
    FROM tabs
    WHERE table_name = nombreTabla;
    
    -- Si la tabla no existe, se crea con 'execute immediate'
    IF si_esta_tabla_creada = 0 THEN
        dbms_output.put_line('La tabla no existe');
        EXECUTE IMMEDIATE tabla;
        dbms_output.put_line('La tabla ' || nombreTabla || ' ha sido creada con exito');
    ELSE -- Si la tabla ya existe, se informa al usuario
        dbms_output.put_line('La tabla ' || nombreTabla || ' ya estaba creada');
    END IF;
END crea_tabla_inversiones;