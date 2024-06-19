
--- ARCHIVO: INSERTOCONSISTENTE-Esqueleto.sql

-------------- PASOS A IMPLEMENTAR  del PROCEDIMIENTO insertoConsistente
     --> Se asume que YA has ejecutado los ejemplos ejecutables 
     --> del Tema PLSQL >> Ejercicios y ejemplos--PLSQL >> PLSQLejemplosEjecutablesTeoria-para-CV.zip


create or replace PROCEDURE insertoConsistente (

DNI_p        invierte.DNI%TYPE,
NombreE_p    invierte.NombreE%TYPE,
Cantidad_p   invierte.Cantidad%TYPE,
Tipo_p       invierte.Tipo%TYPE
)  AS


-- variables de trabajo para decidir en qu� CASO estoy

es_dni_nuevo int := 0;  -- tendra un 0 si el DNI es nuevo
es_tipo_nuevo int := 0;  -- tendra un 0 si el tipo es nuevo
es_empresa_nueva int := 0;    -- tendra un 0 si la empresa es nueva


-- VARS para excepciones 
      Tcoderror NUMBER;
      Ttexterror VARCHAR2(100);



BEGIN

DBMS_output.put_line('Aqu� empieza INSERTOCONSISTENTE');

-- muestro los datos de entrada (par�metros) con los que trabajo
   

       --- CONSULTAS a partir de los Par�metros, para distinguir cada CASO: 0, 1, 2, 3 y 4 --
       
-- Decido si ese DNI es nuevo (no tiene inversiones) : si 0 es nuevo
   -- una select que cuente si hay filas que cumplan lo que buscas y asigna el resultado a
   -- la variable es_dni_nuevo


-- Decido si es Tipo nuevo para ese cliente: si 0 es nuevo
   -- otra select  parecida a la anterior  (into es_tipo_nuevo)


-- Decido si es empresa nueva para ese cliente: si 0 es nuevo
   -- otra select parecida a la anterior  (into es_empresa_nueva)


-- imprimo el resultado de los contadores de las consultas, , indican en el caso que estamos


---------- SEG�N el CASO HAGO el PROCESO


-------- CASO 0.- No hay inversiones de ese DNI: inserto la fila y termino
    -- Pregunto por el contador correspondiente: es_dni_nuevo

--- imprimo la fila nueva



  --- ===  (ELSE) RESTO DE CASOS EN CASCADA  (DNI de entrada ya est� en alguna fila de Invierte == ------


-- ! CASO 1.-  Ya existe una fila con mismo Tipo (1) y Empresa (1) : es un error, no se lo permito 
    -- Pregunto por el contador correspondiente:



-- ! CASO 2.-  tipo nuevo para una  Empresa que ya hay inversiones: debo insertar filas con ese tipo para todas sus empresas


    -- Imprimo cada fila nueva


-- ! CASO 3.- Empresa nueva para un tipo que ya hay inversiones: debo insertar filas con ese empresa para todos sus tipos
--          No tomo en cuenta la nueva cantidad (es complejo comprobar la antig�a si hay varias empresas con ese Tipo)


-- Imprimo cada fila nueva


-- ! CASO 4.- El tipo y la empresa son nuevos: Como  CASO 2 + CASO 3

  ------ para cada empresa que hab�a tengo que insertar el bono nuevo

   -- Imprimo cada fila nueva



  ------- para esta empresa nueva tengo que insertar todos los bonos que hab�a 
  --      (como incluye el bono nuevo, que est� ya en la BD, genera tambi�n 
  --         la fila de los argumentos de entrada)


   -- Imprimo cada fila nueva

EXCEPTION

  WHEN OTHERS THEN
	Tcoderror:= SQLCODE;
	Ttexterror:= SUBSTR(SQLERRM,1, 100);
   DBMS_output.put_line('Sale por una excepcion: ' || Tcoderror ||   '  -- ' || Ttexterror );
   DBMS_output.put_line('$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$' ); 


END;
