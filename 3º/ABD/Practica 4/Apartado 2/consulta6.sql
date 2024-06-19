---- CONSULTA 6 --- delete plan_table;
EXPLAIN PLAN INTO plan_table
FOR(
select distinct NombreC
from Cliente, Compras, Invierte
where Cliente.DNI = Invierte.DNI and Invierte.NombreE = 'Empresa 55' and
Compras.DNI = Cliente.DNI and Compras.Importe >1000);
select operation,options,object_name,cost,cardinality,parent_id,id

from plan_table connect by prior id=parent_id
start with id = 1 order by id;