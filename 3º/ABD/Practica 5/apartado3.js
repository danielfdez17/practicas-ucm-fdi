// * A) 1.
db.aficiones.aggregate([
  { $match: { Puntuacion: { $gte: 9 } } },
  { $project: { _id: 0, Nombre: 1, Tema: 1, Puntuacion: 1 } },
]);

// * A) 2.
db.aficiones.aggregate([
  {
    $group: { nombre: "$Tema", totalGastado: { $sum: "$Precio" } },
    totalComponentes: { $sum: 1 },
  },
]);

// * A) 3.
db.aficiones.aggregate([
  { $match: { Puntuacion: { $gt: 4, $lt: 9 } } },
  {
    $group: {
      _id: "$Puntuacion",
      Componentes: { $push: { Nombre: "$Nombre", Tema: "$Tema" } },
    },
  },
  { $sort: { _id: -1 } },
]);

// * A) 4.
db.aficiones.aggregate([
  {
    $group: {
      _id: "$Tema",
      Apodos: { $addToSet: "$Apodo" },
    },
  },
]);

// * B)
var cursor = db.aficiones.aggregate([
  {
    $group: {
      _id: { Tema: "$Tema", Nombre: "$Nombre" },
      Apodos: { $addToSet: "$Apodo" },
    },
  },
  {
    $match: {
      "Apodos.1": { $exists: true },
    },
  },
  {
    $project: {
      _id: 0,
      Tema: "$_id.Tema",
      Nombre: "$_id.Nombre",
      Apodos: 1,
    },
  },
]);

while (cursor.hasNext()) {
  printjson(cursor.next());
}

// * C)
db.aficiones.aggregate([
  {
    $match: {
      Puntuacion: { $gt: 4, $lt: 9 }, // Puntuaciones intermedias (más de 4 y menos de 9)
    },
  },
  {
    $group: {
      _id: { Tema: "$Tema", Nombre: "$Nombre", Puntuacion: "$Puntuacion" },
      Apodos: { $addToSet: "$Apodo" },
    },
  },
  {
    $project: {
      _id: 0,
      Tema: "$_id.Tema",
      Nombre: "$_id.Nombre",
      Puntuacion: "$_id.Puntuacion",
      Apodos: 1,
    },
  },
]);

// * E) 1.
var cursor = db.aficiones.find().sort({ Tema: 1 }); // Ordena los documentos por tema
cursor.forEach((componente) => {
  print("TEMA: " + componente.Tema + " - NombreDoc: " + componente.Nombre);
});

// * E) 2.
db.aficiones.aggregate([
  {
    $group: {
      _id: "$Tema",
      Documentos: { $push: "$Nombre" },
      Cantidad: { $sum: 1 },
    },
  },
]);

// * F)
// Función para calcular el descuento basado en la puntuación
function calcularDescuento(puntuacion) {
  // Inventa una fórmula para calcular el descuento basado en la puntuación
  // Por ejemplo, podríamos hacer algo como 100 - (puntuacion * 10)
  return 100 - puntuacion * 10;
}
// Rebajar un 10% al precio de todos los componentes peor valorados (puntuación < 7) y asignar el atributo Descuento a todas las aficiones
db.aficiones.find({ Puntuacion: { $lt: 7 } }).forEach(function (componente) {
  // Calculamos el nuevo precio con el descuento
  var nuevoPrecio = componente.Precio * 0.9; // Rebaja del 10%
  // Calculamos el descuento basado en la puntuación
  var descuento = calcularDescuento(componente.Puntuacion);
  // Mostramos información sobre el componente antes de la actualización
  print("Actualizando componente con ID:", componente._id);
  print(
    "Precio anterior:",
    componente.Precio,
    "Nuevo precio con descuento:",
    nuevoPrecio
  );
  print("Descuento aplicado:", descuento);
  // Actualizamos el componente en la base de datos con el nuevo precio y el descuento
  db.aficiones.updateOne(
    { _id: componente._id },
    {
      $set: {
        Precio: nuevoPrecio,
        Descuento: descuento,
      },
    }
  );
});

// * G) 1.
// Crear la colección PorNivel y agregar los documentos
db.createCollection("PorNivel");

// Definir los intervalos de calidad y sus límites
var niveles = [
  { NomCal: "nivel_1", rango: { min: 0, max: 30 } },
  { NomCal: "nivel_2", rango: { min: 30, max: 50 } },
  { NomCal: "nivel_3", rango: { min: 50, max: 70 } },
  { NomCal: "nivel_4", rango: { min: 70, max: Infinity } },
];

// Iterar sobre cada nivel y agregar los componentes correspondientes
niveles.forEach(function (nivel) {
  var componentes = [];
  db.aficiones
    .find({ Puntuacion: { $exists: true } })
    .forEach(function (componente) {
      var valorCalidad = componente.Puntuacion * 10;
      if (valorCalidad >= nivel.rango.min && valorCalidad <= nivel.rango.max) {
        // Agregar el componente al array con su valor de calidad calculado
        componentes.push({
          Nombre: componente.Nombre,
          Precio: componente.Precio,
          ValorCalidad: valorCalidad,
        });
      }
    });

  // Insertar el documento PorNivel para este nivel
  db.PorNivel.insertOne({
    NomCal: nivel.NomCal,
    Componentes: componentes,
  });
});

// * G) 3.
// Imprimir el contenido de la colección PorNivel formateado
db.PorNivel.find().forEach(function (nivel) {
  print("Nivel: " + nivel.NomCal);
  nivel.Componentes.forEach(function (componente) {
    print(
      "Nombre: " +
        componente.Nombre +
        ", Precio: " +
        componente.Precio +
        ", ValorCalidad: " +
        componente.ValorCalidad
    );
  });
  print("-----------------------------------------");
});

// * G) 4.
db.aficiones.aggregate([
  // Ordena los elementos por precio de menor a mayor
  { $sort: { Precio: 1 } },
  // Limita los resultados a los 5 elementos más baratos
  { $limit: 5 },
  // Proyecta solo los campos necesarios (Nombre, Precio y NomCal)
  { $project: { _id: 0, Nombre: 1, Precio: 1, NomCal: 1 } },
]);

// * G) 5.
// Eliminar los 2 componentes más caros de cada intervalo (NomCal)
niveles.forEach(function (nivel) {
  // Obtener los componentes ordenados por precio de forma descendente
  var componentes = db.PorNivel.findOne({ NomCal: nivel.NomCal }).Componentes;
  componentes.sort(function (a, b) {
    return b.Precio - a.Precio;
  });

  // Obtener los IDs de los 2 componentes más caros
  var componentesAEliminar = componentes.slice(0, 2).map(function (componente) {
    return componente._id;
  });

  // Eliminar los componentes más caros
  db.PorNivel.updateOne(
    { NomCal: nivel.NomCal },
    { $pull: { Componentes: { _id: { $in: componentesAEliminar } } } }
  );
});
