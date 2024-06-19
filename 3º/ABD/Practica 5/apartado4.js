// * A)
db.createCollection("superGuai");

// * B)
db.aficiones.find().forEach(function (componente) {
  var calidad = componente.Puntuacion * 10; // Multiplicar la puntuación por 10 para obtener el nivel de calidad
  db.aficiones.update({ _id: componente._id }, { $set: { Calidad: calidad } });
});

// * C)
db.superGuai.insertOne({
  Nombre: "Ejemplo",
  Tema: "Ejemplo",
  Puntuacion: 10,
  Precio: 100,
  Calidad: 100,
});

// * D)
var mejoresComponentes = db.aficiones.find().sort({ Calidad: -1 }).limit(5);
mejoresComponentes.forEach(function (componente) {
  db.superGuai.insertOne(componente);
});
