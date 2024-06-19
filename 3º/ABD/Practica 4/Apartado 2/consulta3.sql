-- CONSULTA 3 -- anidados ----
delete plan_table;
EXPLAIN PLAN
INTO plan_table
FOR select * from cliente where DNI in
(select DNI from moroso where NombreC = 'Client E');
select operation,options,object_name,cost,cardinality,parent_id,id

from plan_table connect by prior id=parent_id
start with id = 1 order by id;