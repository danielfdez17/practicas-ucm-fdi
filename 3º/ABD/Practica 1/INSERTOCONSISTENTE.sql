create or replace PROCEDURE insertoConsistente (



DNI_p        invierte.DNI%TYPE,
NombreE_p    invierte.NombreE%TYPE,
Cantidad_p   invierte.Cantidad%TYPE,
Tipo_p       invierte.Tipo%TYPE
)  AS


-- variables de trabajo para decidir en qu¿ CASO estoy




es_dni_nuevo int := 0;  -- tendra un 0 si el DNI es nuevo
es_tipo_nuevo int := 0;  -- tendra un 0 si el tipo es nuevo
es_empresa_nueva int := 0;    -- tendra un 0 si la empresa es nueva


dni_cursor Invierte.dni%type;
tipo_cursor Invierte.tipo%type;
empresa_cursor Invierte.nombree%type;
cantidad_cursor Invierte.cantidad%type;




-- VARS para excepciones 
      Tcoderror NUMBER;
      Ttexterror VARCHAR2(100);




---Cursores
CURSOR cursor_recorre1 IS
select DNI ,
NOMBREE ,
CANTIDAD ,
TIPO 
from invierte
where dni =  Dni_p;

cursor1 cursor_recorre1%rowtype;

---Cursor
CURSOR cursor_recorre2 IS
select DNI ,
NOMBREE ,
CANTIDAD ,
TIPO 
from invierte
where tipo = Tipo_p;

cursor2 cursor_recorre2%rowtype;

---Exception
error_empresas EXCEPTION;



BEGIN


DBMS_output.put_line('Aqu¿ empieza INSERTOCONSISTENTE');


-- muestro los datos de entrada (par¿metros) con los que trabajo
DBMS_output.put_line(DNI_p || ' '|| NombreE_p  || ' '|| Cantidad_p  || ' '|| Tipo_p);


       --- CONSULTAS a partir de los Par¿metros, para distinguir cada CASO: 0, 1, 2, 3 y 4 --

-- Decido si ese DNI es nuevo (no tiene inversiones) : si 0 es nuevo
   -- una select que cuente si hay filas que cumplan lo que buscas y asigna el resultado a
   -- la variable es_dni_nuevo
  SELECT COUNT(DNI) INTO es_dni_nuevo FROM Invierte
  where DNI = DNI_p;


-- Decido si es Tipo nuevo para ese cliente: si 0 es nuevo
   -- otra select  parecida a la anterior  (into es_tipo_nuevo)
SELECT COUNT(Tipo) INTO es_tipo_nuevo FROM Invierte
where tipo_p = tipo;


-- Decido si es empresa nueva para ese cliente: si 0 es nuevo
   -- otra select parecida a la anterior  (into es_empresa_nueva)
SELECT COUNT(nombree) INTO es_empresa_nueva FROM Invierte
where nombree_p = nombree;


-- imprimo el resultado de los contadores de las consultas, , indican en el caso que estamos
DBMS_output.put_line('DNI: ' || es_dni_nuevo || ' Tipo: ' || es_tipo_nuevo  || ' Empresa: '|| es_empresa_nueva);


---------- SEG¿N el CASO HAGO el PROCESO


-------- CASO 0.- No hay inversiones de ese DNI: inserto la fila y termino
    -- Pregunto por el contador correspondiente: es_dni_nuevo
    IF es_dni_nuevo = 0 THEN
    INSERT INTO Invierte VALUES(DNI_p, NombreE_p , Cantidad_p, Tipo_p);


--- imprimo la fila nueva
    DBMS_output.put_line('DNI: ' || DNI_p || ' Nombre: ' || NombreE_p  || ' Cantidad: '|| Cantidad_p  || ' Tipo: ' || Tipo_p);


  --- ===  (ELSE) RESTO DE CASOS EN CASCADA  (DNI de entrada ya est¿ en alguna fila de Invierte == ------
    ELSE


-- CASO 1.-  Ya existe una fila con mismo Tipo (1) y Empresa (1) : es un error, no se lo permito 
    -- Pregunto por el contador correspondiente:
    IF es_tipo_nuevo <> 0 AND es_empresa_nueva <> 0 THEN
    RAISE error_empresas; 


-- CASO 2.-  tipo nuevo para una  Empresa que ya hay inversiones: debo insertar filas con ese tipo para todas sus empresas
    ELSIF es_tipo_nuevo = 0 AND es_dni_nuevo <> 0 THEN
    FOR cursor1 IN cursor_recorre1
    LOOP
    INSERT INTO Invierte VALUES(cursor1.dni,cursor1.nombree, cursor1.cantidad, Tipo_p);
    -- Imprimo cada fila nueva
    DBMS_output.put_line('DNI: ' || cursor1.dni || ' Nombre: ' || cursor1.nombree  || ' Cantidad: '|| cursor1.cantidad  || ' Tipo: ' || Tipo_p);
    END LOOP;


-- CASO 3.- Empresa nueva para un tipo que ya hay inversiones: debo insertar filas con ese empresa para todos sus tipos
--          No tomo en cuenta la nueva cantidad (es complejo comprobar la antig¿a si hay varias empresas con ese Tipo)
    ELSIF es_empresa_nueva = 0 AND es_tipo_nuevo <> 0 THEN
    FOR cursor2 IN cursor_recorre2
    LOOP
    INSERT INTO Invierte VALUES(cursor2.dni, nombree_p ,cursor2.cantidad, tipo_p);
    -- Imprimo cada fila nueva
    DBMS_output.put_line('DNI: ' || cursor2.dni || ' Nombre: ' || cursor2.nombree  || ' Cantidad: '|| cursor2.cantidad  || ' Tipo: ' || Tipo_p);
    END LOOP;



-- CASO 4.- El tipo y la empresa son nuevos: Como  CASO 2 + CASO 3
    ELSE
     ------ para cada empresa que habia tengo que insertar el bono nuevo
        FOR cursor1 IN cursor_recorre1
    LOOP
    INSERT INTO Invierte VALUES(cursor1.dni,cursor1.nombree, cursor1.cantidad, Tipo_p);
    -- Imprimo cada fila nueva
    DBMS_output.put_line('DNI: ' || cursor1.dni || ' Nombre: ' || cursor1.nombree  || ' Cantidad: '|| cursor1.cantidad  || ' Tipo: ' || Tipo_p);
    END LOOP;
     ------- para esta empresa nueva tengo que insertar todos los bonos que hab¿a 
  --      (como incluye el bono nuevo, que est¿ ya en la BD, genera tambi¿n 
  --         la fila de los argumentos de entrada)
    FOR cursor2 IN cursor_recorre2
    LOOP
    INSERT INTO Invierte VALUES(cursor2.dni, nombree_p ,cursor2.cantidad, tipo_p);
    -- Imprimo cada fila nueva
    DBMS_output.put_line('DNI: ' || cursor2.dni || ' Nombre: ' || cursor2.nombree  || ' Cantidad: '|| cursor2.cantidad  || ' Tipo: ' || Tipo_p);
    END LOOP;
    END IF; 


END IF;


EXCEPTION
    WHEN error_empresas THEN
    DBMS_output.put_line('HA HABIDO UN ERROR$' ); 


  WHEN OTHERS THEN
	Tcoderror:= SQLCODE;
	Ttexterror:= SUBSTR(SQLERRM,1, 100);
   DBMS_output.put_line('Sale por una excepcion: ' || Tcoderror ||   '  -- ' || Ttexterror );
   DBMS_output.put_line('$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$' ); 




END;