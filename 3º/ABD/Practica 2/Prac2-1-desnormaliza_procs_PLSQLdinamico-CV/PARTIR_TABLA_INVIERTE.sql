create or replace procedure Partir_Tabla_Invierte
AS
BEGIN
    FOR fila IN (SELECT * FROM Invierte) LOOP
    Gestion_Inversion(fila.DNI, 
                      fila.NombreE, 
                      fila.Cantidad,
                      fila.Tipo,
                      fila.CodOferta);
    END LOOP;
END Partir_Tabla_Invierte;