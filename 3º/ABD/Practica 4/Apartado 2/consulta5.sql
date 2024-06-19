---- CONSULTA 5 --- delete plan_table; /* borra las tuplas de explicación anterior*/
EXPLAIN PLAN
INTO plan_table
FOR (select * from cliente where dni in
(select dni from invierte where cantidad < 30000));
select operation,options,object_name,cost,cardinality,parent_id,id

from plan_table connect by prior id=parent_id
start with id = 1 order by id;