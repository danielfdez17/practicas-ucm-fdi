-- CONSULTA 4 – ----
delete plan_table;
EXPLAIN PLAN
INTO plan_table
FOR (select * from cliente where dni in
(select dni from invierte));
select operation,options,object_name,cost,cardinality,parent_id,id

from plan_table connect by prior id=parent_id
start with id = 1 order by id;