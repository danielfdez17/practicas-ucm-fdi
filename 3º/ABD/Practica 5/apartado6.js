// * B) 1.
db.aficiones.updateMany(
  { Tema: "MotoGP" },
  { $rename: { NombreEquipo: "Nombre" } }
);

// * B) 2.
db.aficiones
  .find({ $or: [{ Tema: "Fútbol" }, { Tema: "Baloncesto" }] })
  .forEach(function (doc) {
    while (doc.Precio >= 1000 || doc.Descuento >= 10) {
      db.aficiones.updateOne({ _id: doc._id }, [
        {
          $set: {
            Precio: { $divide: ["$Precio", 10] },
            Descuento: { $divide: ["$Descuento", 10] },
          },
        },
      ]);
      doc.Precio /= 10;
      doc.Descuento /= 10;
    }
  });

// * B) 3.
db.aficiones.updateMany(
  { $or: [{ Tema: "MotoGP" }, { Tema: "Ajedrez" }] },
  { $set: { Precio: 100 } }
);

// * B) 4.
db.aficiones.updateMany({ Tema: "Fútbol", Puntuacón: { $exists: true } }, [
  { $set: { Puntuacion: "$Puntuacón" } },
  { $unset: { Puntuacón: "" } },
]);

// * B) 5.
db.aficiones.updateMany({ Tema: "Ajedrez" }, [
  {
    $set: {
      Nombre: {
        $concat: ["$Nombre", " ", "$Apellidos"],
        $unset: ["Apellidos"],
      },
    },
  },
]);

// * D) 1.
db.createCollection("solodatos");

// * D) 2.
db.createCollection("soloaficiones");

// * D) 3.
db.aficiones
  .aggregate([
    { $group: { _id: "$Nombre", detalles: { $first: "$$ROOT" } } },
    { $replaceRoot: { newRoot: "$detalles" } },
  ])
  .forEach(function (doc) {
    db.solodatos.insertOne(doc);
  });

// * D) 4.
db.aficiones.find().forEach(function (doc) {
  var detalles = db.solodatos.findOne({ Nombre: doc.Nombre });
  if (detalles) {
    doc.RefDatos = detalles._id;
    delete doc._id;
    db.soloaficiones.insertOne(doc);
  }
});

// * E)
db.soloAficiones.aggregate([
  {
    $lookup: {
      from: "soloDatos",
      localField: "RefDatos",
      foreignField: "_id",
      as: "RestoDatos",
    },
  },
]);

// * F)
db.solodatos.aggregate([
  {
    $lookup: {
      from: "soloaficiones",
      localField: "_id",
      foreignField: "RefDatos",
      as: "aficiones",
    },
  },
  { $unwind: { path: "$aficiones", preserveNullAndEmptyArrays: true } },
  { $replaceRoot: { newRoot: { $mergeObjects: ["$aficiones", "$$ROOT"] } } },
  { $project: { aficiones: 0 } },
  { $addFields: { new_id: { $toString: "$_id" } } },
  {
    $replaceRoot: {
      newRoot: { $mergeObjects: [{}, "$$ROOT", { _id: "$$new_id" }] },
    },
  },
  { $project: { new_id: 0 } },
  { $out: "reconstruida" },
]);
