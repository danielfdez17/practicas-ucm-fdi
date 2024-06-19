CREATE TABLE SumaEmpresa (
    NombreE CHAR(8) PRIMARY KEY,
    Cantidad FLOAT,
    FOREIGN KEY (NombreE) REFERENCES Empresa (NombreE)
);