declare
 varz CHAR(20) := '''  algo  xx xx ''';
 varx CHAR(30) := REPLACE(varz, ' ', '');
begin 
DBMS_OUTPUT.PUT_LINE('que sale : ' || varx);
end;


/*  ejecucion :

que sale : 'algoxxxx' 


*/

