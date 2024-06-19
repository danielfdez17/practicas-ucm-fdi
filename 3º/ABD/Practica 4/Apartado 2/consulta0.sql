-- CONSULTA 0 -- delete plan_table;
EXPLAIN PLAN INTO plan_table
FOR (select * from cliente where DNI <> '00000005') union
(select * from moroso where NombreC = 'Client E');
--> Puedes usa F10 para tener más detalles
select operation,options,object_name,cost,cardinality,parent_id,id
from plan_table connect by prior id=parent_id
start with id = 1 order by id;