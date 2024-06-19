-- CONSULTA 1 --
delete plan_table; /* primero borra las filas de explicación anterior */
EXPLAIN PLAN
INTO plan_table
FOR (select * from cliente where DNI < '00000005') union
(select * from moroso where NombreC = 'Client E');
select operation,options,object_name,cost,cardinality,parent_id,id

from plan_table connect by prior id=parent_id
start with id = 1 order by id;